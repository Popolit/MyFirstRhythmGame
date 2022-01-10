#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start(GeneralSetting*& generalSetting)
{
	//변수 셋팅
	{
		this->generalSetting = generalSetting;

		Selection = ConstValue::OptionList::Sync;
		IsSelected = false;
		IsSettingChanged = true;

		SyncValue = generalSetting->getSyncValue();
		SpeedValue = generalSetting->getSpeed();
		generalSetting->getKeys(Keys);
	}

	//Image 셋팅
	{
		Background.Content = "PlayBG";
		Background.Length = { 1280, 720 };

		OptionUnderLine.Content = "Pixel";
		OptionUnderLine.Location = { -50, 270 };
		OptionUnderLine.Length = { 1100, 5 };
	}
	
	//인터페이스 텍스트 설정
	{
		OptionText.Content = "OPTION";
		OptionText.Font = { "CookieRun Bold", 50, true };
		OptionText.Location = { 150, 50 };
		OptionText.Length = { 200, 50 };
		OptionText.Color = { 255, 255, 255 };


		IndiSync.Content = "싱크 : ";
		IndiSync.Font = { "CookieRun Bold", 30, true };
		IndiSync.Location = { 400, 250 };
		IndiSync.Length = { 200, 40 };
		IndiSync.Color = { 255, 255, 255 };

		IndiSpeed.Content = "속도 : ";
		IndiSpeed.Font = { "CookieRun Bold", 30, true };
		IndiSpeed.Location = { 400, 350 };
		IndiSpeed.Length = { 200, 40 };
		IndiSpeed.Color = { 255, 255, 255 };

		IndiKeys.Content = "키 설정 : ";
		IndiKeys.Font = { "CookieRun Bold", 30, true };
		IndiKeys.Location = { 380, 450 };
		IndiKeys.Length = { 200, 40 };
		IndiKeys.Color = { 255, 255, 255 };
	}
	
	
	//옵션 수치 설정
	{
		TextSyncValue.Font = { "CookieRun Bold", 30, true };
		TextSyncValue.Location = { 880, 250 };
		TextSyncValue.Length = { 200, 40 };
		TextSyncValue.Color = { 255, 255, 255 };

		TextSpeedValue.Font = { "CookieRun Bold", 30, true };
		TextSpeedValue.Location = { 880, 350 };
		TextSpeedValue.Length = { 200, 40 };
		TextSpeedValue.Color = { 255, 255, 255 };

		for (UINT u = 0; u < 4; u++)
		{
			TextKeys[u].Font = { "CookieRun Bold", 30, true };
			TextKeys[u].Location = { 675 + u * 100, 450 };
			TextKeys[u].Length = { 90, 40 };
			TextKeys[u].Color = { 255, 255, 255 };

			KeysBox[u].Content = "KeysBox";
			KeysBox[u].Location = { 0 + u * 100, -85 };
			KeysBox[u].Length = { 90, 90 };
		}
	}

	AnimSelect.Content = "SelectMode";
	AnimSelect.Location = { 360, -80 };
	AnimSelect.Length = { 24, 24 };
	AnimSelect.Duration = 2;
	AnimSelect.Repeatable = true;
}

ConstValue::SceneList OptionScene::UpdateScene() 
{
	Camera.Set();
	Background.Draw();
	OptionText.Draw();
	OptionUnderLine.Draw();
	IndiSync.Draw();
	IndiSpeed.Draw();
	IndiKeys.Draw();
	AnimSelect.Draw();

	std::string str_sync = std::to_string(SyncValue);
	TextSyncValue.Content = str_sync.data();
	TextSyncValue.Draw();

	std::string str_speed = std::to_string(SpeedValue);
	str_speed = str_speed.substr(0, str_speed.find_first_of('.') + 2 * sizeof(char));
	TextSpeedValue.Content = str_speed.data();
	TextSpeedValue.Draw();

	std::string str_keys[4];
	for (UINT u = 0; u < 4; u++)
	{
		str_keys[u] = Keycode::toString(Keys[u]);
		TextKeys[u].Content = str_keys[u].data();
		TextKeys[u].Draw();
		KeysBox[u].Draw();
	}
	AnimSelect.Location[1] = 100 - 100 * static_cast<float>(Selection);
	//수정할 옵션 선택
	if (!IsSelected)
	{
		if (Input::Get::Key::Down(VK_DOWN))++Selection;
		if (Input::Get::Key::Down(VK_UP)) --Selection;
		if (Input::Get::Key::Down(VK_RETURN)) IsSelected = true;	
		if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	}
	//선택한 옵션 수정
	else
	{		
		switch (Selection)
		{
			case ConstValue::OptionList::Sync:
			{
				if (Input::Get::Key::Down(VK_UP)) SyncValue++;
				if (Input::Get::Key::Down(VK_DOWN)) SyncValue--;
				break;
			}
			case ConstValue::OptionList::Speed:
			{
				if (Input::Get::Key::Down(VK_UP)) SpeedValue += 0.5f;
				if (Input::Get::Key::Down(VK_DOWN)) SpeedValue -= 0.5f;
				break;
			}
			case ConstValue::OptionList::Keys:
			{
				if (KeyIndex == 4)
				{
					KeyIndex = 0;
					IsSelected = false;
				}
				else
				{
					auto it = Keycode::KeyMap.begin();
					for (; it != Keycode::KeyMap.end(); it++)
					{
						if (Input::Get::Key::Down(it->first))
						{
							Keys[KeyIndex] = it->first;
							KeyIndex++;
							break;
						}
					}
					
				}
				break;
			}
		}
		if (Input::Get::Key::Down(VK_RETURN) || Input::Get::Key::Down(VK_ESCAPE)) IsSelected = false;
	}
	return ConstValue::SceneList::Option;
}
void OptionScene::End() 
{
	if (IsSettingChanged)
	{
		generalSetting->setSyncValue(SyncValue);
		generalSetting->setSpeed(SpeedValue);
		generalSetting->setKeys(Keys);
		IsSettingChanged = false;
	}
}
void OptionScene::PlaySong() {}