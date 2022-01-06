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

    JudgePhrase.Length = { 300, 100 };
    JudgePhrase.Location = { -300, 0 };
    this->generalSetting = generalSetting;
    
    Chart chart = Chart("Sample");
  
    chart.makeNotes(Notes);
    for (UINT u = 0; u < 4; u++)
    {
        nextNodeIndex[u] = 0;
        noteCount[u] = Notes[u].size();
    }

    timed = 0.0f;
}

UINT PlayScene::Update()
{
    using namespace ConstValue;
    Judge judges[4] = { None, None, None, None };
    timed += Time::Get::Delta();

    if (Input::Get::Key::Down(keys[0])) nextNodeIndex[0] = 44;//judges[0] = Notes[0][nextNodeIndex[0]].Judge(static_cast<UINT>(timed * 1000));
    if (Input::Get::Key::Down(keys[1])) judges[1] = Notes[1][nextNodeIndex[1]].Judge(static_cast<UINT>(timed * 1000));
    if (Input::Get::Key::Down(keys[2])) judges[2] = Notes[2][nextNodeIndex[2]].Judge(static_cast<UINT>(timed * 1000));
    if (Input::Get::Key::Down(keys[3])) judges[3] = Notes[3][nextNodeIndex[3]].Judge(static_cast<UINT>(timed * 1000));

    Camera.Location[1] +=  500 * Time::Get::Delta();
    Background.Location[1] +=   500 * Time::Get::Delta();
    Lane.Location[1] += 500 * Time::Get::Delta();
    
    Camera.Set();
    
    Background.Draw();
    Lane.Draw();
    for (UINT u = 0; u < 4; u++)
    {
        switch (judges[u])
        {
            case Perfect:
            {
                nextNodeIndex[u]++;
                JudgePhrase.Content = "Perfect";
                JudgePhrase.Draw();
                break;
            }
            case Good:
            {
                nextNodeIndex[u]++;
                JudgePhrase.Content = "Perfect";
                JudgePhrase.Draw();
                break;
            }
            case Miss:
            {
                nextNodeIndex[u]++;
                JudgePhrase.Content = "Perfect";
                JudgePhrase.Draw();
                break;
            }
            case None:
            {
                /*if (Notes[u][nextNodeIndex[u]].getTiming() < timed * 1000 - MissRange)
                {
                    nextNodeIndex[u]++;
                }*/
                break;
            }
        }
        for (UINT noteIndex = nextNodeIndex[u]; noteIndex < noteCount[u]; noteIndex++) Notes[u][noteIndex].DrawNote();
    }
    if (Input::Get::Key::Down(VK_ESCAPE)) { return 0; }
    else { return 1; }
}

void PlayScene::End() { }

void PlayScene::PlaySong() {}