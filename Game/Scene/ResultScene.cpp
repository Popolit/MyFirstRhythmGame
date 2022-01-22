#include "stdafx.h"
#include "ResultScene.h"

void ResultScene::Start()
{
	SM = Resource::Get::SM();
	NowPlaying = Resource::Get::NowPlaying();

	Background.Content = "PlayBG";
	Background.Length = ConstValue::ScreenSize;

	Image.Perfect.Content = "Perfect";
	Image.Perfect.Location = { 20, 130 };
	Image.Perfect.Length = { 150, 50 };
	
	Image.Good.Content = "Good";
	Image.Good.Location = { 20, 80 };
	Image.Good.Length = { 150, 50 };
	
	Image.Miss.Content = "Miss";
	Image.Miss.Location = { 20, 30 };
	Image.Miss.Length = { 150, 50 };
	/*
	Diff.Content = "Easy";
	Diff.Location = { 820,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 300, 100 };
	Diff.Color = { 255, 255, 255 };*/
}

ConstValue::SceneList ResultScene::UpdateScene()
{
	Camera.Set();
	Background.Draw();
	Image.Perfect.Draw();
	Image.Good.Draw();
	Image.Miss.Draw();

	return ConstValue::SceneList::Result;
}

void ResultScene::End() 
{
	SM->BGM.Stop();
}