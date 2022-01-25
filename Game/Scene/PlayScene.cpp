#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start()
{
    //변수 셋팅
    SM = SoundManager::Get();
    pSong = Resource::Get::NowPlaying();
    SpeedValue = Resource::Get::SpeedValue();
    Resource::Get::Keys(MappedKeys);
    pJudgePhrase = new JudgePhrase();
    Timed = -3.0f;
    WaitingTime = 3.0f;
    Waited = false;

    //노트 관련 생성
    Chart* chart = pSong->GetChart(Resource::Get::Diff());
    chart->makeNotes(Notes);
    
    NoteCount.Total = 0;
    NoteCount.Total += chart->GetLongCnt();  //롱노트 갯수 추가
    NoteCount.Processed = 0;
    for (UINT u = 0; u < 4; u++)
    {
        nextNoteIndex[u] = 0;
        noteCount[u] = Notes[u].size();
        NoteCount.Total += static_cast<UINT>(noteCount[u]);
        pHitEffects[u] = new HitEffect();
        pHitEffects[u]->SetLane(u);
    }

    pScore = new Score(NoteCount.Total);
    pCombo = new Combo();

    //드로잉 컴포넌트 셋팅
    Camera.Location = { 0, SpeedValue * (- 300) };

    Background.Content = "PlayBG";
    Background.Length = { 1280, 720 };

    Lane.Content = "Lane";
    Lane.Length = { 500, 720 };
    Lane.Location = { -300, SpeedValue * (- 300) };

    SM->SetBGM();
}

ConstValue::SceneList PlayScene::Update()
{
    using namespace ConstValue;
    
    Timed += Time::Get::Delta();

    Camera.Location[1] += SpeedValue * 100 * Time::Get::Delta();

    if (!Waited && 0 <= Timed)
    {
        Camera.Location[1]= 0;
        Timed = 0.0f;
        SM->BGM.Play();
        Waited = true;
    }

    Lane.Location[1] = Camera.Location[1];
    Background.Location[1] = Camera.Location[1];

    Camera.Set();
    //Background.Draw();
    Lane.Draw();


    Judge judges[4] = { Judge::None, Judge::None, Judge::None, Judge::None };

    for (UINT u = 0; u < 4; u++)
    {
        //모든 노트를 처리함
        if (nextNoteIndex[u] == noteCount[u]) continue;
        //노트를 처리하는 파트
        if (Input::Get::Key::Down(MappedKeys[u]))
        {
            judges[u] = Notes[u][nextNoteIndex[u]].Judge(static_cast<UINT>(Timed * 1000));
            if (judges[u] != Judge::None)
            {
                pJudgePhrase->setJudge(judges[u]);
                pCombo->Update(judges[u]);
                NoteCount.Processed++;

                if (!Notes[u][nextNoteIndex[u]].isLong()) nextNoteIndex[u]++;    
                if (judges[u] != Judge::Miss)
                {
                    pHitEffects[u]->Reset();
                    pScore->Update(judges[u]);
                }
            }
        }
        //롱노트를 누르고 있을 때
        else if (Input::Get::Key::Press(MappedKeys[u]))
        {
            judges[u] = Notes[u][nextNoteIndex[u]].PressedJudge(static_cast<UINT>(Timed * 1000));
            if (judges[u] == Judge::Miss)
            {
                pJudgePhrase->setJudge(judges[u]);
                nextNoteIndex[u]++;
                NoteCount.Processed++;
                pCombo->Update(judges[u]);
            }
        }
        //롱노트 떼는 판정
        else if (Input::Get::Key::Up(MappedKeys[u]))
        {
            judges[u] = Notes[u][nextNoteIndex[u]].UpJudge(static_cast<UINT>(Timed * 1000));
            if (judges[u] != Judge::None)
            {
                pJudgePhrase->setJudge(judges[u]);
                nextNoteIndex[u]++;
                NoteCount.Processed++;
                pHitEffects[u]->Reset();
                pScore->Update(judges[u]);
                pCombo->Update(judges[u]);
            }
        }
        //조작하지 않고 Miss라인을 넘어간 노트
        else if (Notes[u][nextNoteIndex[u]].getTiming() < Timed * 1000 - MissRange)
        {
            nextNoteIndex[u]++;
            pCombo->Update(Judge::Miss);
            pJudgePhrase->setJudge(Judge::Miss);
            NoteCount.Processed++;
        }

        for (UINT noteIndex = nextNoteIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
    }

    for(UINT u = 0; u < 4; u++) pHitEffects[u]->Update(Camera.Location[1]);
    pJudgePhrase->Update(Camera.Location[1]);
    pScore->DrawScore();
    pCombo->Draw();


    if (Input::Get::Key::Down(VK_ESCAPE)) 
    {
        SM->BGM.Stop();
        return SceneList::SelectSong; 
    }
    else if (Input::Get::Key::Down(VK_RETURN)) { 
        Resource::Set::NowResult(pScore, pCombo);
        return SceneList::Result; 
    }
    else if (NoteCount.Processed == NoteCount.Total)
    {
        WaitingTime -= Time::Get::Delta();
        if (WaitingTime <= 0)
        {
            Resource::Set::NowResult(pScore, pCombo);
            return SceneList::Result;
        }
        return SceneList::Play;
    }
    else { return SceneList::Play; }
}

void PlayScene::End() 
{
    delete pJudgePhrase; 
    delete pScore;
    delete pCombo;
    for (UINT u = 0; u < 4; u++)
    {
        Notes[u].clear();
        delete pHitEffects[u];
    }
}