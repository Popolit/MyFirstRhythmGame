#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::Start()
{
    Selection = ConstValue::SceneList::SelectSong;

    //이미지
	Background.Content = "TitleScene";
    Background.Length = ConstValue::ScreenSize;

    //애니메이션
    SelectMode.Content = "SelectMode";
    SelectMode.Location = { 360, -80 };
    SelectMode.Length = { 24, 24 };
    SelectMode.Duration = 2;
    SelectMode.Repeatable = true;

    //텍스트
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
    
    SM = SoundManager::Get();
    SM->SetBGM("TitleBGM");
    SM->BGM.Play();
}

ConstValue::SceneList TitleScene::Update()
{
    using namespace ConstValue;

    
    if (Input::Get::Key::Down(VK_UP))
    {
        SM->SE_Move.Play();
        --Selection;
    }
    if (Input::Get::Key::Down(VK_DOWN))
    {
        SM->SE_Move.Play();
        ++Selection;
    }
    if (Input::Get::Key::Down(VK_RETURN))
    {
        SM->SE_Decide.Play();
        return Selection;
    }
    SelectMode.Location[1] = -30.0f - 50 * static_cast<int>(Selection);

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
    SM->BGM.Stop();
}
