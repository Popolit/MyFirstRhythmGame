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

    Notes[0].push_back(Note(120));
    Notes[0][0].MakeNoteImage(0);
}

UINT PlayScene::Update()
{
    if (Input::Get::Key::Down(keys[0])) {}
    if (Input::Get::Key::Down(keys[1])) {}
    if (Input::Get::Key::Down(keys[2])) {}
    if (Input::Get::Key::Down(keys[3])) {}

    Camera.Location[1] +=  500 * Time::Get::Delta();
    Background.Location[1] +=   500 * Time::Get::Delta();
    Lane.Location[1] += 500 * Time::Get::Delta();
    
    Camera.Set();
    
    Background.Draw();
    Lane.Draw();
    Notes[0][0].DrawNote();
    if (Input::Get::Key::Down(VK_ESCAPE)) { return 0; }
    else { return 1; }
}

void PlayScene::End() { }

void PlayScene::PlaySong() {}