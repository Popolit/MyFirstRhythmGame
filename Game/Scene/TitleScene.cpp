#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::Start()
{
    Selection = ConstValue::SceneList::SelectSong;

	Background.Content = "TitleScene";
	Background.Length = { 2560 / 2, 1440 / 2 };

    SelectMode.Content = "SelectMode";
    SelectMode.Location = { 360, -80 };
    SelectMode.Length = { 24, 24 };
    SelectMode.Duration = 2;
    SelectMode.Repeatable = true;

    StartGame.Content = "Game Start";
    StartGame.Location = { 1100, 450 };
    StartGame.Length = { 150, 50 };
    StartGame.Font = { "CookieRun Bold", 30, true };
    StartGame.Color = { 255, 255, 255 };

    Option.Content = "Option";
    Option.Location = { 1100, 500 };
    Option.Length = { 150, 50 };
    Option.Font = { "CookieRun Bold", 30, true};
    Option.Color = { 255, 255, 255 };

    EndGame.Content = "End Game";
    EndGame.Location = { 1100, 550 };
    EndGame.Length = { 150, 50 };
    EndGame.Font = { "CookieRun Bold", 30, true };
    EndGame.Color = { 255, 255, 255 };
    
    BGM.Content = "TitleBGM";
    BGM.volume = 0.1f;
    BGM.loop = true;
    BGM.loopBegin = 0;
    BGM.loopLength = 0; 
    BGM.Play();
}

ConstValue::SceneList TitleScene::UpdateScene()
{
    using namespace ConstValue;
    if (Input::Get::Key::Down(VK_UP))
    {
        if (SceneList::SelectSong < Selection)
        {
            --Selection;
            SelectMode.Location[1] += 50;
        }
    }
    if (Input::Get::Key::Down(VK_DOWN))
    {
        if (Selection < ConstValue::SceneList::End)
        {
            ++Selection;
            SelectMode.Location[1] -= 50;
        }
    }
    if (Input::Get::Key::Down(VK_RETURN))
    {
        GameValue::PlaySE();
        return Selection;
    }

    Camera.Set();
    Background.Draw();
    SelectMode.Draw();
    StartGame.Draw();
    Option.Draw();
    EndGame.Draw();

    return ConstValue::SceneList::Title;
}

void TitleScene::End() 
{
    BGM.Stop();
}

void TitleScene::PlaySong() 
{
}