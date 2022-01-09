#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start(GeneralSetting*& generalSetting)
{
	this->generalSetting = generalSetting;

	Selection = ConstValue::OptionList::Sync;

	Background.Content = "PlayBG";
	Background.Length = { 1280, 720 };
	
	//인터페이스 텍스트 설정
	OptionText.Content = "OPTION";
	OptionText.Font = { "CookieRun Bold", 50, true };
	OptionText.Location = { 150, 50 };
	OptionText.Length = { 200, 50 };
	OptionText.Color = { 255, 255, 255 };
	
	OptionUnderLine.Content = "Pixel";
	OptionUnderLine.Location = { -50, 270 };
	OptionUnderLine.Length = { 1100, 5 };
	
	TextSync.Content = "싱크 : ";
	TextSync.Font = { "CookieRun Bold", 30, true };
	TextSync.Location = { 400, 250 };
	TextSync.Length = { 200, 40 };
	TextSync.Color = { 255, 255, 255 };

	TextSpeed.Content = "속도 : ";
	TextSpeed.Font = { "CookieRun Bold", 30, true };
	TextSpeed.Location = { 400, 350 };
	TextSpeed.Length = { 200, 40 };
	TextSpeed.Color = { 255, 255, 255 };

	TextKeys.Content = "키 설정 : ";
	TextKeys.Font = { "CookieRun Bold", 30, true };
	TextKeys.Location = { 380, 450 };
	TextKeys.Length = { 200, 40 };
	TextKeys.Color = { 255, 255, 255 };
	
	
	CurrentSync.Font = { "CookieRun Bold", 30, true };
	CurrentSync.Location = { 880, 250 };
	CurrentSync.Length = { 200, 40 };
	CurrentSync.Color = { 255, 255, 255 };

	CurrentSpeed.Font = { "CookieRun Bold", 30, true };
	CurrentSpeed.Location = { 880, 350 };
	CurrentSpeed.Length = { 200, 40 };
	CurrentSpeed.Color = { 255, 255, 255 };

	/*
	for (UINT u = 0; u < 4; u++)
	{
		CurrentKeys[u].Content = sprintf(CurrentKeys[u].Content, "%d", Keys[u]);
		CurrentKeys[u].Font = { "CookieRun Bold", 50, true };
		CurrentKeys[u].Location = { 150, 50 };
		CurrentKeys[u].Length = { 200, 50 };
		CurrentKeys[u].Color = { 255, 255, 255 };
	}*/
}

ConstValue::SceneList OptionScene::UpdateScene() 
{
	Camera.Set();
	Background.Draw();
	OptionText.Draw();
	OptionUnderLine.Draw();
	TextSync.Draw();
	TextSpeed.Draw();
	TextKeys.Draw();

	std::string str_sync = std::to_string(generalSetting->getSyncValue());
	CurrentSync.Content = str_sync.data();
	CurrentSync.Draw();
	VK_;

	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	return ConstValue::SceneList::Option;
}
void OptionScene::End() {}
void OptionScene::PlaySong() {}