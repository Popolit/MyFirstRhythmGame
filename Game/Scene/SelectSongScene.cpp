#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//변수 셋팅
	Selection = Resource::Get::SongIndex();
	Diff = Resource::Get::Diff();
	SM = SoundManager::Get();

	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
	pResultScene = nullptr;
	SM->SetBGM(NowPlaying->STR.Title, NowPlaying->Highlight);

	//이미지 셋팅
	Background.Content = "SelectSongBG1";
	Background.Length = ConstValue::ScreenSize;

	Image.Thumbnail.Content = NowPlaying->STR.Title.data();
	Image.Thumbnail.Length = { 350, 350 };
	Image.Thumbnail.Location = { -300, 0 };

	Image.VLine.Content = "Pixel";
	Image.VLine.Length = { 5, 350 };
	Image.VLine.Location = { -20, 0 };

	Image.Rank.Content = "Rank_A"; 
	Image.Rank.Length = { 50, 50 };
	Image.Rank.Location = { 100, -150 };

	//텍스트 셋팅
	Text.Title.Content = NowPlaying->STR.Title.data();
	Text.Title.Location = { 890,  230 };
	Text.Title.Font = { "CookieRun Bold", 40, true };
	Text.Title.Length = { 500, 50 };
	Text.Title.Color = { 255, 255, 255 };

	Text.Artist.Content = NowPlaying->STR.Artist.data();
	Text.Artist.Location = { 890,  300 };
	Text.Artist.Font = { "CookieRun Bold", 30, true };
	Text.Artist.Length = { 500, 50 };
	Text.Artist.Color = { 255, 255, 255 };

	Text.BestScore.Content = BestResult->GetScore().data();
	Text.BestScore.Location = { 890, 530 };
	Text.BestScore.Font = { "CookieRun Bold", 50, true };
	Text.BestScore.Length = { 200, 100 };
	Text.BestScore.Color = { 255, 255, 255 };

	Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).data();
	Text.Diff.Location = { 890,  420 };
	Text.Diff.Font = { "CookieRun Bold", 40, true };
	Text.Diff.Length = { 500, 100 };
	Text.Diff.Color = { 255, 255, 255 };

	SM->BGM.Play();
}

ConstValue::SceneList SelectSongScene::Update()
{
	SM->SetFadeIO();
	if (pResultScene != nullptr)
	{
		if (pResultScene->Update())
		{
			delete pResultScene;
			pResultScene = nullptr;
		}
		return ConstValue::SceneList::SelectSong;
	}

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
		++Diff;
		Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).c_str();
		BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
		Text.BestScore.Content = BestResult->GetScore().data();
	}
	if (Input::Get::Key::Down(VK_DOWN))
	{
		SM->SE_Move.Play();
		--Diff;
		Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).c_str();
		BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
		Text.BestScore.Content = BestResult->GetScore().data();
	}


	if (Input::Get::Key::Down(VK_RETURN))
	{
		SM->SE_Decide.Play();
		Resource::Set::Diff(Diff);
		return ConstValue::SceneList::Play;
	}
	
	Camera.Set();
	//Background.Draw();

	Image.VLine.Draw();
	Image.Rank.Draw();
	Image.Thumbnail.Draw();

	Text.Title.Draw();
	Text.Artist.Draw();
	Text.Diff.Draw();
	Text.BestScore.Draw();


	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	if (Input::Get::Key::Down(VK_F2))
	{
		SM->SE_Decide.Play();
		Resource::Set::NowResult(NowPlaying->BestResults[static_cast<int>(Diff)]);
		pResultScene = new ResultScene(false);
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

	Image.Thumbnail.Content = NowPlaying->STR.Title.data();
	Text.Title.Content = NowPlaying->STR.Title.data();
	Text.Artist.Content = NowPlaying->STR.Artist.data();

	BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
	Text.BestScore.Content = BestResult->GetScore().data();
}

void SelectSongScene::SetDiff(ConstValue::Difficulty const& diff)
{
	Result* rslt = Resource::Get::NowPlaying()->BestResults[static_cast<int>(diff)];
	if (rslt->GetScore() == "1000000") {}
	else if (rslt->IsFC()) {}
}