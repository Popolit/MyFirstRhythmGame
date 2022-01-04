#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::Start()
{
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
    Option.Location = { 1130, 500 };
    Option.Length = { 150, 50 };
    Option.Font = { "CookieRun Bold", 30, true };
    Option.Color = { 255, 255, 255 };

    EndGame.Content = "End Game";
    EndGame.Location = { 1110, 550 };
    EndGame.Length = { 150, 50 };
    EndGame.Font = { "CookieRun Bold", 30, true };
    EndGame.Color = { 255, 255, 255 };
   
}

bool TitleScene::Update()
{
    if (Input::Get::Key::Down(VK_UP))
    {
        if (0 < Selection) Selection--; 

    }
    if (Input::Get::Key::Down(VK_DOWN))
    {
        if (Selection < 2) Selection++;
    }

    SelectMode.Location[1] = -80.0f - static_cast<int>(Selection * 50);
    Camera.Set();

    Background.Draw();

    SelectMode.Draw();
    StartGame.Draw();
    Option.Draw();
    EndGame.Draw();

    if (Input::Get::Key::Down(VK_ESCAPE)) { return true; }
    else { return false; }
}

void TitleScene::End() { }