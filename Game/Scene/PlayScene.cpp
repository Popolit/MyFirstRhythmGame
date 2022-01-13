#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start()
{
    //���� ����
    {
        SpeedValue = GameValue::Get::SpeedValue();
        GameValue::Get::Keys(MappedKeys);
        judgePhrase = new JudgePhrase();
        judgePhrase->Start();
        timed = 0.0f;

        Chart chart = Chart("Sample");
        chart.makeNotes(Notes);

        UINT totalNoteCount = 0;
        for (UINT u = 0; u < 4; u++)
        {
            nextNodeIndex[u] = 0;
            noteCount[u] = Notes[u].size();
            totalNoteCount += static_cast<UINT>(noteCount[u]);
            hitEffects[u] = new HitEffect();
            hitEffects[u]->Start();
            hitEffects[u]->setLane(u);
        }

        CurrentScore = new Score(totalNoteCount);
    }
    //����� ������Ʈ ����
    {
        Camera.Location = { 0, 0 };

        Background.Content = "PlayBG";
        Background.Length = { 1280, 720 };

        Lane.Content = "Lane";
        Lane.Length = { 500, 720 };
        Lane.Location = { -300, 0 };
    }
    //�뷡 ����
    {
        Song.Content = "Sample";
        Song.volume = 1;
        Song.Play();
    }
}

ConstValue::SceneList PlayScene::UpdateScene()
{
    using namespace ConstValue;
    Judge judges[4] = { Judge::None, Judge::None, Judge::None, Judge::None };
    timed += Time::Get::Delta();

    Camera.Location[1] += SpeedValue * 100 * Time::Get::Delta();
    Background.Location[1] += SpeedValue * 100 * Time::Get::Delta();
    Lane.Location[1] += SpeedValue * 100 * Time::Get::Delta();
    Camera.Set();
    
    Background.Draw();
    Lane.Draw();
    for (UINT u = 0; u < 4; u++)
    {
        //��� ��Ʈ�� ó����
        if (nextNodeIndex[u] == noteCount[u]) continue;
        //��Ʈ�� ó���ϴ� ��Ʈ
        if (Input::Get::Key::Down(MappedKeys[u]))
        {
            judges[u] = Notes[u][nextNodeIndex[u]].Judge(static_cast<UINT>(timed * 1000));
            if (judges[u] != Judge::None)
            {
                nextNodeIndex[u]++;
                judgePhrase->setJudge(judges[u]);
                if (judges[u] != Judge::Miss)
                {
                    CurrentScore->Update(judges[u]);
                    hitEffects[u]->reset();
                }
            }
        }
        //�������� �ʰ� Miss������ �Ѿ ��Ʈ
        else if (Notes[u][nextNodeIndex[u]].getTiming() < timed * 1000 - MissRange)
        {
            nextNodeIndex[u]++;
            judgePhrase->setJudge(Judge::Miss);
        }
        for (UINT noteIndex = nextNodeIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
        
    }

    for(UINT u = 0; u < 4; u++) hitEffects[u]->Update();
    judgePhrase->Update();
    CurrentScore->DrawScore();
    if (Input::Get::Key::Down(VK_ESCAPE)) { return SceneList::Title; }
    else { return SceneList::Play; }
}

void PlayScene::End() 
{
    Song.Stop();
    delete judgePhrase; 
    //delete CurrentScore;
    for (UINT u = 0; u < 4; u++)
    {
        Notes[u] = std::vector<Note>();
        delete hitEffects[u];
    }
}

void PlayScene::PlaySong() {}