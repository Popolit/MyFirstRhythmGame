#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start()
{
	//변수 셋팅
	Selection = ConstValue::OptionList::Sync;
	KeyIndex = 0;
	Str.Sync = std::to_string(GameValue::Get::SyncValue());
	Str.Speed = std::to_string(GameValue::Get::SpeedValue());
	Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
	//Str.Volume = 
	GameValue::Get::Keys(MappedKeys);
	for (UINT u = 0; u < 4; u++) Str.Keys[u] = Keycode::toString(MappedKeys[u]);
	IsSelected = false;


	//Image 셋팅
	Background.Content = "PlayBG";
	Background.Length = { 1280, 720 };

	OptionUnderLine.Content = "Pixel";
	OptionUnderLine.Location = { -5, 270 };
	OptionUnderLine.Length = { 1170, 5 };

	ArrowUp.Content = "ArrowUp";
	ArrowUp.Location = { 450, 0 };
	ArrowUp.Length = { 25, 25 };
		
	ArrowDown.Content = "ArrowDown";
	ArrowDown.Location = { 450, 0 };
	ArrowDown.Length = { 25, 25 };

	ArrowSelection.Content = "ArrowSelection";
	ArrowSelection.Location = { 450, 270 };
	ArrowSelection.Length = { 50, 25 };
	
	//인터페이스 텍스트 설정
	OptionText.Content = "OPTION";
	OptionText.Font = { "CookieRun Bold", 50, true };
	OptionText.Location = { 150, 50 };
	OptionText.Length = { 200, 50 };
	OptionText.Color = { 255, 255, 255 };


	IndiSync.Content = "싱크 : ";
	IndiSync.Font = { "CookieRun Bold", 30, true };
	IndiSync.Location = { 300, 250 };
	IndiSync.Length = { 200, 40 };
	IndiSync.Color = { 255, 255, 255 };

	IndiSpeed.Content = "속도 : ";
	IndiSpeed.Font = { "CookieRun Bold", 30, true };
	IndiSpeed.Location = { 300, 350 };
	IndiSpeed.Length = { 200, 40 };
	IndiSpeed.Color = { 255, 255, 255 };

	IndiKeys.Content = "키 설정 : ";
	IndiKeys.Font = { "CookieRun Bold", 30, true };
	IndiKeys.Location = { 300, 450 };
	IndiKeys.Length = { 200, 40 };
	IndiKeys.Color = { 255, 255, 255 };
	
	
	//옵션 수치 설정
	TextSyncValue.Content = Str.Sync.data();
	TextSyncValue.Font = { "CookieRun Bold", 30, true };
	TextSyncValue.Location = { 790, 255 };
	TextSyncValue.Length = { 200, 40 };
	TextSyncValue.Color = { 255, 255, 255 };

	TextSpeedValue.Content = Str.Speed.data();
	TextSpeedValue.Font = { "CookieRun Bold", 30, true };
	TextSpeedValue.Location = { 790, 355 };
	TextSpeedValue.Length = { 200, 40 };
	TextSpeedValue.Color = { 255, 255, 255 };

	for (UINT u = 0; u < 4; u++)
	{
		TextKeys[u].Content = Str.Keys[u].data();
		TextKeys[u].Font = { "CookieRun Bold", 25, true };
		TextKeys[u].Location = { 640 + u * 100, 480 };
		TextKeys[u].Length = { 70, 70 };
		TextKeys[u].Color = { 255, 255, 255 };

		KeyBox[u].Content = "KeyBox";
		KeyBox[u].Location = { 0 + u * 100, -100 };
		KeyBox[u].Length = { 90, 90 };
	}
}

ConstValue::SceneList OptionScene::UpdateScene() 
{
	using namespace GameValue;
	Camera.Set();
	Background.Draw();
	OptionText.Draw();
	OptionUnderLine.Draw();
	IndiSync.Draw();
	IndiSpeed.Draw();
	IndiKeys.Draw();

	TextSyncValue.Draw();
	TextSpeedValue.Draw();
	for (UINT u = 0; u < 4; u++)
	{
		TextKeys[u].Draw();
		KeyBox[u].Draw();
	}


	//수정할 옵션 선택
	if (!IsSelected)
	{		
		ArrowSelection.Location[1] = 100 - 100 * static_cast<float>(Selection);
		ArrowSelection.Draw();

		if (Input::Get::Key::Down(VK_DOWN))
		{
			PlaySEMove();
			++Selection;
		}
		if (Input::Get::Key::Down(VK_UP))
		{
			PlaySEMove();
			--Selection;
		}
		if (Input::Get::Key::Down(VK_RETURN))
		{
			PlaySEDecide();
			IsSelected = true;
		}
		if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	}

	//선택한 옵션 수정
	else
	{	
		ArrowUp.Location[1] = 130 - 100 * static_cast<float>(Selection);
		ArrowDown.Location[1] = 100 - 100 * static_cast<float>(Selection);

		switch (Selection)
		{
			case ConstValue::OptionList::Sync:
			{
				int sync = Get::SyncValue();
				if (Input::Get::Key::Down(VK_UP))
				{
					PlaySEMove();		
					Set::SyncValue(++sync);
					Str.Sync = std::to_string(sync);
				}
				if (Input::Get::Key::Down(VK_DOWN))
				{
					PlaySEMove();
					Set::SyncValue(--sync);
					Str.Sync = std::to_string(sync);
				}
				ArrowUp.Draw();
				ArrowDown.Draw();
				break;
			}
			case ConstValue::OptionList::Speed:
			{
				float SpeedValue = Get::SpeedValue();
				if (Input::Get::Key::Down(VK_UP) && SpeedValue < ConstValue::MaxSpeed)
				{
					GameValue::PlaySEMove();
					SpeedValue += 0.5f;
					Set::SpeedValue(SpeedValue);
					Str.Speed = std::to_string(SpeedValue);
					Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
				}
				if (Input::Get::Key::Down(VK_DOWN) && SpeedValue > ConstValue::MinSpeed)
				{
					GameValue::PlaySEMove();
					SpeedValue -= 0.5f;
					Set::SpeedValue(SpeedValue);
					Str.Speed = std::to_string(SpeedValue);
					Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
				}
				ArrowUp.Draw();
				ArrowDown.Draw();
				break;
			}
			case ConstValue::OptionList::Keys:
			{
				//키 설정 완료
				if (KeyIndex == 4)
				{
					KeyIndex = 0;
					IsSelected = false;
				}
				else
				{
					KeyBox[KeyIndex].Content = "KeyBoxSelected";
					size_t PressedKey = Input::Get::Key::GetPressedKey();		

					if (PressedKey == VK_ESCAPE)
					{
						KeyIndex = 0;
						KeyBox[KeyIndex].Content = "KeyBox";
						IsSelected = false;
						break;
					}

					//유효한 키일 때
					if (Keycode::toString(PressedKey) != "")
					{	
						bool IsAlreadyMapped = false;

						//이전 키와 겹치면 무시
						for (UINT u = 0; u < KeyIndex; u++)
						{
							if (MappedKeys[u] == PressedKey)
							{
								IsAlreadyMapped = true;
								break;
							}
						}					
						if (!IsAlreadyMapped)
						{
							GameValue::PlaySEDecide();
							Str.Keys[KeyIndex] = Keycode::toString(PressedKey);
							KeyBox[KeyIndex].Content = "KeyBox";
							MappedKeys[KeyIndex] = PressedKey;
							KeyIndex++;
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
	GameValue::Set::Keys(MappedKeys);
}