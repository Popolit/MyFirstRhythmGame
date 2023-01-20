#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start()
{
    //변수 셋팅
    SM = SoundManager::Get();
    pSong = Resource::Get::NowPlaying();
    SpeedValue = Resource::Get::SpeedValue();
    Resource::Get::Keys(MappedKeys);
    pResult = nullptr;
    pJudgePhrase = new JudgePhrase();
    pResultScene = nullptr;
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
        pKeybeam[u] = new Keybeam();
        pHitEffects[u]->SetLane(u);
        pKeybeam[u]->SetLane(u);
    }

    pScore = new Score(NoteCount.Total);
    pCombo = new Combo();

    //드로잉 컴포넌트 셋팅
    Camera.Location = { 0, SpeedValue * (-300) };

    Background.Content = "PlayBG";
    Background.Length = { 1280, 720 };

    Lane.Content = "Lane";
    Lane.Length = { 500, 720 };
    Lane.Location = { -300, SpeedValue * (-300) };

    SM->SetBGM();
}

ConstValue::SceneList PlayScene::Update()
{
    using namespace ConstValue;

    //게임 종료 후 결과 창 표기
    if (pResultScene != nullptr)
    {
        if (pResultScene->Update())
        {
            SM->BGM.Stop();
            return SceneList::SelectSong;
        }
        return SceneList::Play;
    }

    Timed += Time::Get::Delta();
    Camera.Location[1] += SpeedValue * 100 * Time::Get::Delta();

    //게임 시작 후 대기시간 3초를 세어
    //게임 시간을 0 + 맞춘 싱크초로 초기화
    if (!Waited && 0.f <= Timed)
    {
        Camera.Location[1] = 0;
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

    //4라인에 대하여
    for (UINT u = 0; u < 4; u++)
    {
        pKeybeam[u]->Draw(Camera.Location[1]);
        //모든 노트를 처리하면 종료
        if (nextNoteIndex[u] == noteCount[u]) continue;

        //처리할 노트가 롱노트인지 확인
        bool isLong = Notes[u][nextNoteIndex[u]].isLong();
        //노트를 처리하는 파트
        if (Input::Get::Key::Down(MappedKeys[u]))
        {
            pKeybeam[u]->Update();
            judges[u] = Notes[u][nextNoteIndex[u]].Judge(static_cast<UINT>(Timed * 1000));
            if (judges[u] != Judge::None)
            {
                pJudgePhrase->Update(judges[u]);
                pCombo->Update(judges[u]);
                NoteCount.Processed++;

                if (!isLong) nextNoteIndex[u]++;
                if (judges[u] != Judge::Miss)
                {
                    pHitEffects[u]->Update(isLong);
                    pScore->Update(judges[u]);
                }
                //MIss, Long Note
                else if (isLong)
                {
                    nextNoteIndex[u]++;
                    NoteCount.Processed++;
                }
            }
        }
        //롱노트를 누르고 있을 때
        else if (Input::Get::Key::Press(MappedKeys[u]))
        {
            pKeybeam[u]->Pressing();
            judges[u] = Notes[u][nextNoteIndex[u]].PressedJudge(static_cast<UINT>(Timed * 1000));

            if (judges[u] == Judge::Miss)
            {
                pJudgePhrase->Update(judges[u]);
                nextNoteIndex[u]++;
                NoteCount.Processed++;
                pCombo->Update(judges[u]);
            }
            if (judges[u] != Judge::None) pHitEffects[u]->Update(true);

        }
        //롱노트 떼는 판정
        else if (Input::Get::Key::Up(MappedKeys[u]) && isLong)
        {
            judges[u] = Notes[u][nextNoteIndex[u]].UpJudge(static_cast<UINT>(Timed * 1000));
            if (judges[u] != Judge::None)
            {
                pJudgePhrase->Update(judges[u]);
                nextNoteIndex[u]++;
                NoteCount.Processed++;
                pHitEffects[u]->Update(true);
                pScore->Update(judges[u]);
                pCombo->Update(judges[u]);
            }
        }
        //조작하지 않고 Miss라인을 넘어간 노트
        else if (Notes[u][nextNoteIndex[u]].getTiming() < Timed * 1000 - MissRange)
        {
            nextNoteIndex[u]++;
            pCombo->Update(Judge::Miss);
            pJudgePhrase->Update(Judge::Miss);
            NoteCount.Processed++;
            if (isLong)
                NoteCount.Processed++;
        }

        for (UINT noteIndex = nextNoteIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].Draw();
    }

    for (UINT u = 0; u < 4; u++) pHitEffects[u]->Draw(Camera.Location[1]);
    pJudgePhrase->Draw(Camera.Location[1]);
    pScore->Draw();
    pCombo->Draw();


    if (Input::Get::Key::Down(VK_ESCAPE))
    {
        SM->BGM.Stop();
        return SceneList::SelectSong;
    }
    else if (Input::Get::Key::Down(VK_RETURN)) {
        pResult = new Result(pScore, pCombo);
        pSong->ResultUpdate(pResult);
        pResultScene = new ResultScene(pResult);
    }
    else if (NoteCount.Processed == NoteCount.Total)
    {
        WaitingTime -= Time::Get::Delta();
        if (WaitingTime <= 0)
        {
            pResult = new Result(pScore, pCombo);
            pSong->ResultUpdate(pResult);
            pResultScene = new ResultScene(pResult);
        }
    }
    return SceneList::Play;
}

void PlayScene::End()
{
    delete pJudgePhrase;
    delete pScore;
    delete pCombo;
    delete pResultScene;
    if (pResult != nullptr) delete pResult;
    for (UINT u = 0; u < 4; u++)
    {
        Notes[u].clear();
        delete pKeybeam[u];
        delete pHitEffects[u];
    }
}