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
    this->generalSetting->getKeys(keys);

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

ConstValue::SceneList PlayScene::UpdateScene()
{
    using namespace ConstValue;
    Judge judges[4] = { Judge::None, Judge::None, Judge::None, Judge::None };
    timed += Time::Get::Delta();

    Camera.Location[1] +=  500 * Time::Get::Delta();
    Background.Location[1] +=   500 * Time::Get::Delta();
    Lane.Location[1] += 500 * Time::Get::Delta();
    Camera.Set();
    
    Background.Draw();
    Lane.Draw();
    for (UINT u = 0; u < 4; u++)
    {
        //모든 노트를 처리함
        if (nextNodeIndex[u] == noteCount[u]) continue;
        //노트를 처리하는 파트
        if (Input::Get::Key::Down(keys[u]))
        {
            judges[u] = Notes[u][nextNodeIndex[u]].Judge(static_cast<UINT>(timed * 1000));
            if (judges[u] != Judge::None)
            {
                nextNodeIndex[u]++;
                judgePhrase->setJudge(judges[u]);
                if (judges[u] != Judge::Miss)  hitEffects[u]->reset();
            }
        }
        //조작하지 않고 Miss라인을 넘어간 노트
        else if (Notes[u][nextNodeIndex[u]].getTiming() < timed * 1000 - MissRange)
        {
            nextNodeIndex[u]++;
            judgePhrase->setJudge(Judge::Miss);
        }
        for (UINT noteIndex = nextNodeIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
        
    }
    for(UINT u = 0; u < 4; u++) hitEffects[u]->Update();

    judgePhrase->Update();
    if (Input::Get::Key::Down(VK_ESCAPE)) { return SceneList::Title; }
    else { return SceneList::Play; }
}

void PlayScene::End() 
{ 
    delete judgePhrase; 
    for (UINT u = 0; u < 4; u++)
    {
        Notes[u] = std::vector<Note>();
        delete hitEffects[u];
    }
}

void PlayScene::PlaySong() {}