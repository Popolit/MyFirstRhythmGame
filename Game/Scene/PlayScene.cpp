#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start()
{
    //���� ����
    {
        SpeedValue = GameValue::Get::SpeedValue();
        GameValue::Get::Keys(MappedKeys);
        GameValue::Get::pChart()->makeNotes(Notes);
        judgePhrase = new JudgePhrase();
        judgePhrase->Start();
        timed = 0.0f;

        UINT totalNoteCount = 0;
        for (UINT u = 0; u < 4; u++)
        {
            nextNoteIndex[u] = 0;
            noteCount[u] = Notes[u].size();
            totalNoteCount += static_cast<UINT>(noteCount[u]);
            hitEffects[u] = new HitEffect();
            hitEffects[u]->Start();
            hitEffects[u]->setLane(u);
        }

        CurrentScore = new Score(totalNoteCount);
        CurrentCombo = new Combo();
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
        Song.Content = "Chronomia";
        Song.loop = false;
        Song.volume = 0.1f;
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
        if (nextNoteIndex[u] == noteCount[u]) continue;
        //��Ʈ�� ó���ϴ� ��Ʈ
        if (Input::Get::Key::Down(MappedKeys[u]))
        {
            judges[u] = Notes[u][nextNoteIndex[u]].Judge(static_cast<UINT>(timed * 1000));
            if (judges[u] != Judge::None)
            {
                nextNoteIndex[u]++;
                judgePhrase->setJudge(judges[u]);
                CurrentCombo->Update(judges[u]);
                if (judges[u] != Judge::Miss)
                {
                    CurrentScore->Update(judges[u]);
                    hitEffects[u]->reset();
                }
            }
        }
        //�������� �ʰ� Miss������ �Ѿ ��Ʈ
        else if (Notes[u][nextNoteIndex[u]].getTiming() < timed * 1000 - MissRange)
        {
            nextNoteIndex[u]++;
            CurrentCombo->Update(Judge::Miss);
            judgePhrase->setJudge(Judge::Miss);
        }
        for (UINT noteIndex = nextNoteIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
    }

    for(UINT u = 0; u < 4; u++) hitEffects[u]->Update();
    judgePhrase->Update();
    CurrentScore->DrawScore();
    CurrentCombo->Draw();
    if (Input::Get::Key::Down(VK_ESCAPE)) { return SceneList::SelectSong; }
    else { return SceneList::Play; }
}

void PlayScene::End() 
{
    Song.Stop();
    delete judgePhrase; 
    delete CurrentScore;
    delete CurrentCombo;
    for (UINT u = 0; u < 4; u++)
    {
        Notes[u].clear();
        delete hitEffects[u];
    }
}

void PlayScene::PlaySong() {}