#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//���� ����
	Selection = Resource::Get::SongIndex();
	Diff = Resource::Get::Diff();
	SM = SoundManager::Get();

	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
	pResultScene = nullptr;
	SM->SetBGM(NowPlaying->STR.Title, NowPlaying->Highlight);

	//�̹��� ����
	Background.Content = "SelectSongBG";
	Background.Length = ConstValue::ScreenSize;

	Image.Thumbnail.Content = NowPlaying->STR.Title.data();
	Image.Thumbnail.Length = { 300, 300 };
	Image.Thumbnail.Location = { -300, 0 };

	Image.IndiBar.Content = "IndiBar";
	Image.IndiBar.Length = { 1280, 70 };
	Image.IndiBar.Location = { 0, -325 };

	Image.VLine.Content = "Pixel";
	Image.VLine.Length = { 5, 330 };
	Image.VLine.Location = { -20, 0 };

	Image.Rank.Content = ConstValue::RankToImg.at(BestResult->GetRank()).data();
	Image.Rank.Length = { 50, 50 };
	Image.Rank.Location = { 100, -140 };

	Image.ArrowLeft.Content = "ArrowLeft";
	Image.ArrowLeft.Length = { 80, 80 };
	Image.ArrowLeft.Location = { -550, 0 };

	Image.ArrowRight.Content = "ArrowRight";
	Image.ArrowRight.Length = { 80, 80 };
	Image.ArrowRight.Location = { 550, 0 };



	//�ؽ�Ʈ ����
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

	Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).data();
	Text.Diff.Location = { 890,  420 };
	Text.Diff.Font = { "CookieRun Bold", 40, true };
	Text.Diff.Length = { 500, 100 };
	Text.Diff.Color = { 255, 255, 255 };

	Text.BestScore.Content = BestResult->GetScore().data();
	Text.BestScore.Location = { 890, 520 };
	Text.BestScore.Font = { "CookieRun Bold", 50, true };
	Text.BestScore.Length = { 200, 100 };
	Text.BestScore.Color = { 255, 255, 255 };

	SM->BGM.Play();
}

ConstValue::SceneList SelectSongScene::Update()
{
	SM->SetFadeIO();

	//��� ȭ���� ������ ���
	if (pResultScene != nullptr)
	{
		if (pResultScene->Update())
		{
			delete pResultScene;
			pResultScene = nullptr;
		}
		return ConstValue::SceneList::SelectSong;
	}

	//�� ����
	if (Input::Get::Key::Down(VK_LEFT))
	{
		SetSelection(--Selection);
	}
	if (Input::Get::Key::Down(VK_RIGHT))
	{
		SetSelection(++Selection);
	}
	//���̵� ����
	if (Input::Get::Key::Down(VK_UP))
	{
		Resource::Set::Diff(++Diff);
		SetDiff();
	}
	if (Input::Get::Key::Down(VK_DOWN))
	{		
		Resource::Set::Diff(--Diff);
		SetDiff();
	}


	if (Input::Get::Key::Down(VK_RETURN))
	{
		return ConstValue::SceneList::Play;
	}
	
	Camera.Set();
	Background.Draw();

	Image.VLine.Draw();
	Image.Rank.Draw();
	Image.Thumbnail.Draw();
	Image.IndiBar.Draw();
	Image.ArrowLeft.Draw();
	Image.ArrowRight.Draw();
	

	Text.Title.Draw();
	Text.Artist.Draw();
	Text.Diff.Draw();
	Text.BestScore.Draw();


	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
	//F5 �Է½�, ���â�� ������
	if (Input::Get::Key::Down(VK_F5))
	{
		SM->SE_Decide.Play();
		pResultScene = new ResultScene();
	}
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End()
{
	if (pResultScene != nullptr)
	{
		pResultScene = nullptr;
		delete pResultScene;
	}
	SM->BGM.Stop();
}


//���� ����
void SelectSongScene::SetSelection(int &Selection)
{
	SM->BGM.Stop();
	Resource::Set::NowPlaying(Selection);
	NowPlaying = Resource::Get::NowPlaying();
	SM->SetBGM(NowPlaying->STR.Title, NowPlaying->Highlight);
	SM->BGM.Play();

	Image.Thumbnail.Content = NowPlaying->STR.Title.data();
	Text.Title.Content = NowPlaying->STR.Title.data();
	Text.Artist.Content = NowPlaying->STR.Artist.data();

	SetDiff();
}

//���̵��� ����
void SelectSongScene::SetDiff()
{
	SM->SE_Move.Play();
	Text.Diff.Content = ConstValue::DiffToStr.at(Diff).c_str();

	BestResult = NowPlaying->BestResults[static_cast<int>(Diff)];
	Text.BestScore.Content = BestResult->GetScore().data();
	Image.Rank.Content = ConstValue::RankToImg.at(BestResult->GetRank()).data();
}