#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start(GeneralSetting*& generalSetting)
{
	this->generalSetting = generalSetting;

	Background.Content = "TitleScene";
	Background.Length = { 1280, 720 };
	
	
}

ConstValue::SceneList OptionScene::UpdateScene() 
{
	Camera.Set();
	Background.Draw();
	return ConstValue::SceneList::Option;
}
void OptionScene::End() {}
void OptionScene::PlaySong() {}