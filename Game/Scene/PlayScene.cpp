#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start(GeneralSetting *&generalSetting)
{
    Camera.Location = { 0, 0 };

    Background.Content = "PlayBG";
    Background.Length = { 1280, 720 };

    Lane.Content = "Lane";
    Lane.Length = { 500, 720 };
    Lane.Location = { -300, 0 };

    this->generalSetting = generalSetting;
    generalSetting->getKeys(keys);

    Chart chart = Chart("Sample");
    chart.makeNotes(Notes);
    for (UINT u = 0; u < 4; u++)
    {
        nextNodeIndex[u] = 0;
        noteCount[u] = Notes[u].size();
        hitEffects[u] = new HitEffect();
        hitEffects[u]->Start();
        hitEffects[u]->setLane(u);
    }

    judgePhrase = new JudgePhrase();
    judgePhrase->Start();
    timed = 0.0f;
}

UINT PlayScene::Update()
{
    using namespace ConstValue;
    Judge judges[4] = { None, None, None, None };
    timed += Time::Get::Delta();

    Camera.Location[1] +=  500 * Time::Get::Delta();
    Background.Location[1] +=   500 * Time::Get::Delta();
    Lane.Location[1] += 500 * Time::Get::Delta();
    Camera.Set();
    
    Background.Draw();
    Lane.Draw();
    for (UINT u = 0; u < 4; u++)
    {
        //��� ��Ʈ�� ó����
        if (nextNodeIndex[u] == noteCount[u]) continue;
        //��Ʈ�� ó���ϴ� ��Ʈ
        if (Input::Get::Key::Down(keys[u]))
        {
            judges[u] = Notes[u][nextNodeIndex[u]].Judge(static_cast<UINT>(timed * 1000));
            if (judges[u] != None)
            {
                nextNodeIndex[u]++;
                judgePhrase->setJudge(judges[u]);
                if (judges[u] != Miss)  hitEffects[u]->reset();
            }
        }
        //�������� �ʰ� Miss������ �Ѿ ��Ʈ
        else if (Notes[u][nextNodeIndex[u]].getTiming() < timed * 1000 - MissRange)
        {
            nextNodeIndex[u]++;
        }
        for (UINT noteIndex = nextNodeIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
        
    }
    for(UINT u = 0; u < 4; u++) hitEffects[u]->Update();

    judgePhrase->Update();
    if (Input::Get::Key::Down(VK_ESCAPE)) { return 0; }
    else { return 1; }
}

void PlayScene::End() 
{ 
    delete judgePhrase; 
    for (UINT u = 0; u < 4; u++)
    {
        delete hitEffects[u];
    }
}

void PlayScene::PlaySong() {}