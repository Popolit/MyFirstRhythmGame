#include "stdafx.h"
#include "TestScene.h"

void TestScene::Start()
{
    Background.Content = "Celadon";
    Background.Length = { 960 * 4, 703 * 4 };

    Player.Content = "Fio";
    Player.Length = { 384 / 3 , 384 / 3 };
    Player.Duration = 1;
    Player.Repeatable = true;
}

bool TestScene::Update()
{
    Vector<2> direction;

    if (Input::Get::Key::Press(VK_LEFT))  direction[0] -= 1;
    if (Input::Get::Key::Press(VK_RIGHT)) direction[0] += 1;
    if (Input::Get::Key::Press(VK_UP))    direction[1] += 1;
    if (Input::Get::Key::Press(VK_DOWN))  direction[1] -= 1;

    if (Length(direction) != 0)
    {
        Camera.Location += Normalize(direction) * 500 * Time::Get::Delta();
        Player.Location += Normalize(direction) * 500 * Time::Get::Delta();
    }

    Camera.Set();

    Background.Draw();

    Player.Draw();

    if (Input::Get::Key::Down(VK_ESCAPE)) { return true; }
    else { return false; }
}

void TestScene::End() { }