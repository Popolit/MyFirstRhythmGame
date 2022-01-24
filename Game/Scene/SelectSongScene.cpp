#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//변수 셋팅
	Selection = 0;
	SongCount = Resource::Get::SongCount();
	Difficulty = ConstValue::Difficulty::Easy;
	SM = SoundManager::Get();

	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	SM->SetBGM(NowPlaying->GetTitle(), NowPlaying->GetHighlight());

	//이미지 셋팅
	Background.Content = "SelectSongBG1";
	Background.Length = ConstValue::ScreenSize;

	Diff.Content = "Easy";
	Diff.Location = { 890,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 500, 100 };
	Diff.Color = { 255, 255, 255 };
	SM->BGM.Play();
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
	//곡 변경
	if (Input::Get::Key::Down(VK_LEFT) && 0 < Selection)
	{
		SM->SE_Move.Play();
		SM->BGM.Stop();
		Selection--;
		Resource::Set::NowPlaying(Selection);
		NowPlaying = Resource::Get::NowPlaying();
		SM->SetBGM(NowPlaying->GetTitle(), NowPlaying->GetHighlight());
		SM->BGM.Play();
	}
	if (Input::Get::Key::Down(VK_RIGHT) && Selection < SongCount - 1)
	{
		SM->SE_Move.Play();
		SM->BGM.Stop();
		Selection++;
		Resource::Set::NowPlaying(Selection);
		NowPlaying = Resource::Get::NowPlaying();
		SM->SetBGM(NowPlaying->GetTitle(), NowPlaying->GetHighlight());
		SM->BGM.Play();
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


	if (Input::Get::Key::Down(VK_RETURN))
	{
		SM->SE_Decide.Play();
		Resource::Set::Diff(Difficulty);
		return ConstValue::SceneList::Play;
	}
	
	Camera.Set();
	//Background.Draw();
	Diff.Draw();

	NowPlaying->Draw();
	SM->SetFadeIO();

	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End() 
{
	SM->BGM.Stop();
}