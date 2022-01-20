#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//변수 셋팅
	Selection = 0;
	Difficulty = ConstValue::Difficulty::Easy;
	SM = Resource::Get::SM();
	NowPlaying = Resource::Get::SongAt(Selection);
	SM->SetBGM(NowPlaying->GetTitle(), NowPlaying->GetHighlight());

	//이미지 셋팅
	Background.Content = "SelectSongBG1";
	Background.Length = ConstValue::ScreenSize;

	Diff.Content = "Easy";
	Diff.Location = { 820,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 300, 100 };
	Diff.Color = { 255, 255, 255 };

	SM->BGM.Play();
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
	//곡 변경
	if (Input::Get::Key::Down(VK_LEFT) && 0 < Selection)
	{
		SM->SE_Move.Play();
		Difficulty = ConstValue::Difficulty::Easy;
		Selection--;
	}
	if (Input::Get::Key::Down(VK_RIGHT) && Selection < SongCount - 1)
	{
		SM->SE_Move.Play();
		Difficulty = ConstValue::Difficulty::Easy;
		Selection++;
	}
	if (Input::Get::Key::Down(VK_UP))
	{
		SM->SE_Move.Play();
		++Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}
	if (Input::Get::Key::Down(VK_DOWN))
	{
		SM->SE_Move.Play();
		--Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}

	/*
	//곡이 끝나기 2초전 페이드아웃
	else if (LoopLength < 2.0f)
	{
		Volume -= SM->Volume * Time::Get::Delta() / 2;
		selectedSong->song.volume = Volume;
		selectedSong->song.SetVolume();
	}
	//페이드 인
	else if (Volume < SM->Volume)
	{
		Volume += SM->Volume * Time::Get::Delta() / 2;
		selectedSong->song.volume = Volume;
		selectedSong->song.SetVolume();
	}
	*/
	Camera.Set();
	Background.Draw();

	Diff.Draw();

	/*
	if (Input::Get::Key::Down(VK_RETURN))
	{
		SM->SE_Decide.Play();
		switch (Difficulty)
		{
			case ConstValue::Difficulty::Easy:
			{
				Resource::Set::pChart(selectedSong->Easy);
				break;
			}
			case ConstValue::Difficulty::Normal:
			{
				Resource::Set::pChart(selectedSong->Normal);
				break;
			}
			case ConstValue::Difficulty::Hard:
			{
				Resource::Set::pChart(selectedSong->Hard);
				break;
			}
		}
		return ConstValue::SceneList::Play;
	}*/
	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End() {}