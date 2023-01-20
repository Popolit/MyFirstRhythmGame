#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Start()
{
    //���� ����
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

    //��Ʈ ���� ����
    Chart* chart = pSong->GetChart(Resource::Get::Diff());
    chart->makeNotes(Notes);

    NoteCount.Total = 0;
    NoteCount.Total += chart->GetLongCnt();  //�ճ�Ʈ ���� �߰�
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

    //����� ������Ʈ ����
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

    //���� ���� �� ��� â ǥ��
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

    //���� ���� �� ���ð� 3�ʸ� ����
    //���� �ð��� 0 + ���� ��ũ�ʷ� �ʱ�ȭ
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

    //4���ο� ���Ͽ�
    for (UINT u = 0; u < 4; u++)
    {
        pKeybeam[u]->Draw(Camera.Location[1]);
        //��� ��Ʈ�� ó���ϸ� ����
        if (nextNoteIndex[u] == noteCount[u]) continue;

        //ó���� ��Ʈ�� �ճ�Ʈ���� Ȯ��
        bool isLong = Notes[u][nextNoteIndex[u]].isLong();
        //��Ʈ�� ó���ϴ� ��Ʈ
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
        //�ճ�Ʈ�� ������ ���� ��
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
        //�ճ�Ʈ ���� ����
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
        //�������� �ʰ� Miss������ �Ѿ ��Ʈ
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