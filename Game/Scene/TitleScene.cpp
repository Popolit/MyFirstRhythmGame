#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::Start()
{
	Background.Content = "TitleScene";
	Background.Length = { 2560 / 2, 1440 / 2 };

   /* SelectArrow.Content = "";
    SelectArrow.Length = {};
    SelectArrow.Duration = 1;
    SelectArrow.Repeatable = true;*/

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
    UINT Selection = 0;

    if (Input::Get::Key::Down(VK_UP))    Selection--;
    if (Input::Get::Key::Down(VK_DOWN))  Selection++;

    Camera.Set();

    Background.Draw();
    StartGame.Draw();
    Option.Draw();
    EndGame.Draw();

    if (Input::Get::Key::Down(VK_ESCAPE)) { return true; }
    else { return false; }
}

void TitleScene::End() { }