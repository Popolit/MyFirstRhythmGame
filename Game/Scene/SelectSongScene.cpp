#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//변수 셋팅
	Selection = Resource::Get::SongIndex();
	Difficulty = Resource::Get::Diff();
	SM = SoundManager::Get();

	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	SM->SetBGM(NowPlaying->STR.Title, NowPlaying->Highlight);

	//이미지 셋팅
	Background.Content = "SelectSongBG1";
	Background.Length = ConstValue::ScreenSize;

	Thumbnail.Content = NowPlaying->STR.Title.data();
	Thumbnail.Length = { 350, 350 };
	Thumbnail.Location = { -300, 0 };

	VLine.Content = "Pixel";
	VLine.Length = { 5, 350 };
	VLine.Location = { -20, 0 };

	//텍스트 셋팅
	Title.Content = NowPlaying->STR.Title.data();
	Title.Location = { 890,  230 };
	Title.Font = { "CookieRun Bold", 40, true };
	Title.Length = { 500, 50 };
	Title.Color = { 255, 255, 255 };

	Artist.Content = NowPlaying->STR.Artist.data();
	Artist.Location = { 890,  300 };
	Artist.Font = { "CookieRun Bold", 30, true };
	Artist.Length = { 500, 50 };
	Artist.Color = { 255, 255, 255 };

	Diff.Content = ConstValue::ToString(Difficulty).c_str();
	Diff.Location = { 890,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 500, 100 };
	Diff.Color = { 255, 255, 255 };

	SM->BGM.Play();
}

ConstValue::SceneList SelectSongScene::Update()
{

	//곡 변경
	if (Input::Get::Key::Down(VK_LEFT))
	{
		SetSelection(--Selection);
	}
	if (Input::Get::Key::Down(VK_RIGHT))
	{
		SetSelection(++Selection);
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

	Thumbnail.Draw();
	Title.Draw();
	Artist.Draw();
	VLine.Draw();

	SM->SetFadeIO();

	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	if (Input::Get::Key::Down(0x44))
	{
		Resource::Set::NowResult(NowPlaying->BestResults[static_cast<int>(Difficulty)]);
		return ConstValue::SceneList::Result;
	}
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End() 
{
	SM->BGM.Stop();
}

void SelectSongScene::SetSelection(int &Selection)
{
	SM->SE_Move.Play();
	SM->BGM.Stop();
	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	SM->SetBGM(NowPlaying->STR.Title, NowPlaying->Highlight);
	SM->BGM.Play();

	Thumbnail.Content = NowPlaying->STR.Title.data();
	Title.Content = NowPlaying->STR.Title.data();
	Artist.Content = NowPlaying->STR.Artist.data();
	
	
}

void SelectSongScene::SetDiff(ConstValue::Difficulty const& diff)
{
	Result* rslt = Resource::Get::NowPlaying()->BestResults[static_cast<int>(diff)];
	if (rslt->GetScore() == "1000000") {}
	else if (rslt->IsFC()) {}


	
}