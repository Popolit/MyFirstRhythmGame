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
    pSong->GetChart(Resource::Get::Diff())->makeNotes(Notes);

    NoteCount.Total = 0;
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

    SM->SetBGM(pSong->GetTitle());
}

ConstValue::SceneList PlayScene::UpdateScene()
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
                nextNoteIndex[u]++;
                pJudgePhrase->setJudge(judges[u]);
                pCombo->Update(judges[u]);
                NoteCount.Processed++;
                if (judges[u] != Judge::Miss)
                {
                    pScore->Update(judges[u]);
                    pHitEffects[u]->Reset();
                }
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
        return SceneList::Result; }
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