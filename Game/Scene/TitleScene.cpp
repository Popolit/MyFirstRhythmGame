#include "stdafx.h"
#include "TitleScene.h"

ConstValue::SceneList operator++(ConstValue::SceneList& sl)
{
    return sl = sl == ConstValue::SceneList::End ? ConstValue::SceneList::End : static_cast<ConstValue::SceneList>(static_cast<int>(sl) + 1);
}
ConstValue::SceneList operator--(ConstValue::SceneList& sl)
{
    return sl = sl == ConstValue::SceneList::Title ? ConstValue::SceneList::Title : static_cast<ConstValue::SceneList>(static_cast<int>(sl) - 1);
}

bool operator<(ConstValue::SceneList &A, ConstValue::SceneList & B)
{
    return static_cast<UINT> (A) < static_cast<UINT> (B);
}

void TitleScene::Start(GeneralSetting *&generalSetting)
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
    Option.Location = { 1130, 500 };
    Option.Length = { 150, 50 };
    Option.Font = { "CookieRun Bold", 30, true};
    Option.Color = { 255, 255, 255 };

    EndGame.Content = "End Game";
    EndGame.Location = { 1110, 550 };
    EndGame.Length = { 150, 50 };
    EndGame.Font = { "CookieRun Bold", 30, true };
    EndGame.Color = { 255, 255, 255 };
   
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
    if (Input::Get::Key::Down(VK_RETURN)) return Selection;

    Camera.Set();

    Background.Draw();

    SelectMode.Draw();
    StartGame.Draw();
    Option.Draw();
    EndGame.Draw();

    return ConstValue::SceneList::Title;
}

void TitleScene::End() { }

void TitleScene::PlaySong() { }