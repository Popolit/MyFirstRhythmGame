#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start()
{
	//변수 셋팅
	SM = SoundManager::Get();

	Selection = ConstValue::OptionList::Sync;
	KeyIndex = 0;
	Str.Sync = std::to_string(Resource::Get::SyncValue());
	Str.Speed = std::to_string(Resource::Get::SpeedValue());
	Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
	Str.Volume = std::to_string(static_cast<UINT>(SM->Volume * 100));
	Resource::Get::Keys(MappedKeys);
	for (UINT u = 0; u < 4; u++) Str.Keys[u] = Keycode::toString(MappedKeys[u]);
	IsSelected = false;


	//Image 셋팅
	Image.UnderLine.Content = "Pixel";
	Image.UnderLine.Location = { -5, 270 };
	Image.UnderLine.Length = { 1170, 5 };

	Image.ArrowUD.Content = "ArrowUpDown";
	Image.ArrowUD.Location = { 450, 170 };
	Image.ArrowUD.Length = { 30, 50 };

	Image.ArrowSelection.Content = "ArrowSelection";
	Image.ArrowSelection.Location = { 450, 170 };
	Image.ArrowSelection.Length = { 40, 40 };
	
	//인터페이스 텍스트 설정
	Text.Option.Content = "OPTION";
	Text.Option.Font = { "CookieRun Bold", 50, true };
	Text.Option.Location = { 150, 50 };
	Text.Option.Length = { 200, 50 };
	Text.Option.Color = { 255, 255, 255 };


	Text.IndiSync.Content = "싱크 : ";
	Text.IndiSync.Font = { "CookieRun Bold", 30, true };
	Text.IndiSync.Location = { 300, 200 };
	Text.IndiSync.Length = { 200, 40 };
	Text.IndiSync.Color = { 255, 255, 255 };

	Text.IndiSpeed.Content = "속도 : ";
	Text.IndiSpeed.Font = { "CookieRun Bold", 30, true };
	Text.IndiSpeed.Location = { 300, 300 };
	Text.IndiSpeed.Length = { 200, 40 };
	Text.IndiSpeed.Color = { 255, 255, 255 };

	Text.IndiVolume.Content = "볼륨 : ";
	Text.IndiVolume.Font = { "CookieRun Bold", 30, true };
	Text.IndiVolume.Location = { 300, 400 };
	Text.IndiVolume.Length = { 200, 40 };
	Text.IndiVolume.Color = { 255, 255, 255 };

	Text.IndiKeys.Content = "키 설정 : ";
	Text.IndiKeys.Font = { "CookieRun Bold", 30, true };
	Text.IndiKeys.Location = { 300, 500 };
	Text.IndiKeys.Length = { 200, 40 };
	Text.IndiKeys.Color = { 255, 255, 255 };

	//옵션 수치 설정
	Text.SyncValue.Content = Str.Sync.data();
	Text.SyncValue.Font = { "CookieRun Bold", 30, true };
	Text.SyncValue.Location = { 790, 200 };
	Text.SyncValue.Length = { 200, 40 };
	Text.SyncValue.Color = { 255, 255, 255 };

	Text.SpeedValue.Content = Str.Speed.data();
	Text.SpeedValue.Font = { "CookieRun Bold", 30, true };
	Text.SpeedValue.Location = { 790, 300 };
	Text.SpeedValue.Length = { 200, 40 };
	Text.SpeedValue.Color = { 255, 255, 255 };

	Text.VolumeValue.Content = Str.Volume.data();
	Text.VolumeValue.Font = { "CookieRun Bold", 30, true };
	Text.VolumeValue.Location = { 790, 400 };
	Text.VolumeValue.Length = { 200, 40 };
	Text.VolumeValue.Color = { 255, 255, 255 };

	for (UINT u = 0; u < 4; u++)
	{
		Text.Keys[u].Content = Str.Keys[u].data();
		Text.Keys[u].Font = { "CookieRun Bold", 25, true };
		Text.Keys[u].Location = { 640 + u * 100, 530 };
		Text.Keys[u].Length = { 70, 70 };
		Text.Keys[u].Color = { 255, 255, 255 };

		Image.KeyBox[u].Content = "KeyBox";
		Image.KeyBox[u].Location = { 0 + u * 100, -150 };
		Image.KeyBox[u].Length = { 90, 90 };
	}
}

ConstValue::SceneList OptionScene::Update() 
{
	using namespace Resource;
	Camera.Set();

	Image.UnderLine.Draw();

	Text.Option.Draw();
	
	Text.IndiSync.Draw();
	Text.IndiSpeed.Draw();
	Text.IndiKeys.Draw();
	Text.IndiVolume.Draw();

	Text.SyncValue.Draw();
	Text.SpeedValue.Draw();
	Text.VolumeValue.Draw();
	
	for (UINT u = 0; u < 4; u++)
	{
		Image.KeyBox[u].Draw();
		Text.Keys[u].Draw();
	}


	//수정할 옵션 선택
	if (!IsSelected)
	{		
		Image.ArrowSelection.Location[1] = 170.0f - 102 * static_cast<int>(Selection);
		Image.ArrowUD.Location[1] = 170.0f - 102 * static_cast<int>(Selection);
		Image.ArrowSelection.Draw();
		if (Input::Get::Key::Down(VK_DOWN))
		{
			SM->SE_Move.Play();
			++Selection;	
		}
		if (Input::Get::Key::Down(VK_UP))
		{
			SM->SE_Move.Play();
			--Selection;
		}
		if (Input::Get::Key::Down(VK_RETURN))
		{
			SM->SE_Decide.Play();
			IsSelected = true;
		}
		if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	}

	//선택한 옵션 수정
	else
	{	
		switch (Selection)
		{
			case ConstValue::OptionList::Sync:
			{
				int sync = Get::SyncValue();
				if (Input::Get::Key::Down(VK_UP))
				{
					SM->SE_Move.Play();
					Set::SyncValue(++sync);				
					Str.Sync = std::to_string(sync);
				}
				if (Input::Get::Key::Down(VK_DOWN))
				{
					SM->SE_Move.Play();
					Set::SyncValue(--sync);
					Str.Sync = std::to_string(sync);
				}
				Image.ArrowUD.Draw();
				break;
			}
			case ConstValue::OptionList::Speed:
			{
				float speed = Get::SpeedValue();
				if (Input::Get::Key::Down(VK_UP) && speed < ConstValue::MaxSpeed)
				{
					SM->SE_Move.Play();
					speed += 0.5f;
					Set::SpeedValue(speed);
					Str.Speed = std::to_string(speed);
					Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
				}
				if (Input::Get::Key::Down(VK_DOWN) && speed > ConstValue::MinSpeed)
				{
					SM->SE_Move.Play();
					speed -= 0.5f;
					Set::SpeedValue(speed);
					Str.Speed = std::to_string(speed);
					Str.Speed = Str.Speed.substr(0, Str.Speed.find_first_of('.') + 2 * sizeof(char));
				}
				Image.ArrowUD.Draw();
				break;
			}
			case ConstValue::OptionList::Volume:
			{
				UINT volume = static_cast<UINT>(SM->Volume * 100);
				if (Input::Get::Key::Down(VK_UP) && volume < 100)
				{
					SM->SE_Move.Play();
					volume += 5;
					SM->SetVolume(volume);
					Str.Volume = std::to_string(volume);
				}
				if (Input::Get::Key::Down(VK_DOWN) && 0 < volume)
				{
					SM->SE_Move.Play();
					volume -= 5;
					Str.Volume = std::to_string(volume);
					SM->SetVolume(volume);
				}
				Image.ArrowUD.Draw();
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
					Image.KeyBox[KeyIndex].Content = "KeyBoxSelected";
					size_t PressedKey = Input::Get::Key::GetPressedKey();		

					if (PressedKey == VK_ESCAPE)
					{
						KeyIndex = 0;
						Image.KeyBox[KeyIndex].Content = "KeyBox";
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
							SM->SE_Move.Play();
							Str.Keys[KeyIndex] = Keycode::toString(PressedKey);
							Image.KeyBox[KeyIndex].Content = "KeyBox";
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
	Resource::Set::Keys(MappedKeys);
}