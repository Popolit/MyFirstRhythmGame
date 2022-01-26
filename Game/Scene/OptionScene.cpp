#include "stdafx.h"
#include "OptionScene.h"

void OptionScene::Start()
{
	//���� ����
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


	//Image ����
	Background.Content = "PlayBG";
	Background.Length = { 1280, 720 };

	Image.UnderLine.Content = "Pixel";
	Image.UnderLine.Location = { -5, 270 };
	Image.UnderLine.Length = { 1170, 5 };

	Image.ArrowUp.Content = "ArrowUp";
	Image.ArrowUp.Location = { 450, 0 };
	Image.ArrowUp.Length = { 25, 25 };
	
	Image.ArrowDown.Content = "ArrowDown";
	Image.ArrowDown.Location = { 450, 0 };
	Image.ArrowDown.Length = { 25, 25 };

	Image.ArrowSelection.Content = "ArrowSelection";
	Image.ArrowSelection.Location = { 450, 270 };
	Image.ArrowSelection.Length = { 50, 25 };
	
	//�������̽� �ؽ�Ʈ ����
	Text.Option.Content = "OPTION";
	Text.Option.Font = { "CookieRun Bold", 50, true };
	Text.Option.Location = { 150, 50 };
	Text.Option.Length = { 200, 50 };
	Text.Option.Color = { 255, 255, 255 };


	Text.IndiSync.Content = "��ũ : ";
	Text.IndiSync.Font = { "CookieRun Bold", 30, true };
	Text.IndiSync.Location = { 300, 200 };
	Text.IndiSync.Length = { 200, 40 };
	Text.IndiSync.Color = { 255, 255, 255 };

	Text.IndiSpeed.Content = "�ӵ� : ";
	Text.IndiSpeed.Font = { "CookieRun Bold", 30, true };
	Text.IndiSpeed.Location = { 300, 300 };
	Text.IndiSpeed.Length = { 200, 40 };
	Text.IndiSpeed.Color = { 255, 255, 255 };

	Text.IndiVolume.Content = "���� : ";
	Text.IndiVolume.Font = { "CookieRun Bold", 30, true };
	Text.IndiVolume.Location = { 300, 400 };
	Text.IndiVolume.Length = { 200, 40 };
	Text.IndiVolume.Color = { 255, 255, 255 };

	Text.IndiKeys.Content = "Ű ���� : ";
	Text.IndiKeys.Font = { "CookieRun Bold", 30, true };
	Text.IndiKeys.Location = { 300, 500 };
	Text.IndiKeys.Length = { 200, 40 };
	Text.IndiKeys.Color = { 255, 255, 255 };

	//�ɼ� ��ġ ����
	Text.SyncValue.Content = Str.Sync.data();
	Text.SyncValue.Font = { "CookieRun Bold", 30, true };
	Text.SyncValue.Location = { 790, 205 };
	Text.SyncValue.Length = { 200, 40 };
	Text.SyncValue.Color = { 255, 255, 255 };

	Text.SpeedValue.Content = Str.Speed.data();
	Text.SpeedValue.Font = { "CookieRun Bold", 30, true };
	Text.SpeedValue.Location = { 790, 305 };
	Text.SpeedValue.Length = { 200, 40 };
	Text.SpeedValue.Color = { 255, 255, 255 };

	Text.VolumeValue.Content = Str.Volume.data();
	Text.VolumeValue.Font = { "CookieRun Bold", 30, true };
	Text.VolumeValue.Location = { 790, 405 };
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
	Background.Draw();

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


	//������ �ɼ� ����
	if (!IsSelected)
	{		
		Image.ArrowSelection.Location[1] = 150 - 100 * static_cast<float>(Selection);
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

	//������ �ɼ� ����
	else
	{	
		Image.ArrowUp.Location[1] = 180 - 100 * static_cast<float>(Selection);
		Image.ArrowDown.Location[1] = 150 - 100 * static_cast<float>(Selection);

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
				Image.ArrowUp.Draw();
				Image.ArrowDown.Draw();
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
				Image.ArrowUp.Draw();
				Image.ArrowDown.Draw();
				break;
			}
			case ConstValue::OptionList::Volume:
			{
				UINT volume = static_cast<UINT>(SM->Volume * 100);
				if (Input::Get::Key::Down(VK_UP) && volume < 100)
				{
					SM->SE_Move.Play();
					volume += 5;
					SM->SetVolume(SM->Volume + 0.05f);
					Str.Volume = std::to_string(volume);
				}
				if (Input::Get::Key::Down(VK_DOWN) && 0 < volume)
				{
					SM->SE_Move.Play();
					volume -= 5;
					SM->Volume -= 0.05f;
					Str.Volume = std::to_string(volume);
					SM->SetVolume(SM->Volume - 0.05f);
				}
				Image.ArrowUp.Draw();
				Image.ArrowDown.Draw();
				break;
			}
			case ConstValue::OptionList::Keys:
			{
				//Ű ���� �Ϸ�
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

					//��ȿ�� Ű�� ��
					if (Keycode::toString(PressedKey) != "")
					{	
						bool IsAlreadyMapped = false;

						//���� Ű�� ��ġ�� ����
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