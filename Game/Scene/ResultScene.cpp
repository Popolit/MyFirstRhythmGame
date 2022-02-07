#include "stdafx.h"
#include "ResultScene.h"

ResultScene::ResultScene(Result* newResult)
{
	//변수 셋팅
	SM = SoundManager::Get();
	pSong = Resource::Get::NowPlaying();
	if (newResult == nullptr) pResult = pSong->BestResults[static_cast<int>(Resource::Get::Diff())];
	else pResult = newResult;

	//이미지 셋팅
	Background.Content = "PlayBG";
	Background.Length = ConstValue::ScreenSize;

	Image.Thumbnail.Content = pSong->STR.Title.data();
	Image.Thumbnail.Length = { 350, 350 };
	Image.Thumbnail.Location = { -300, 0 };

	Image.VLine.Content = "Pixel";
	Image.VLine.Length = { 5, 350 };
	Image.VLine.Location = { -20, 0 };

	Image.Perfect.Content = "Perfect";
	Image.Perfect.Location = { 100, -30 };
	Image.Perfect.Length = { 150, 50 };
	
	Image.Good.Content = "Good";
	Image.Good.Location = { 100, -80 };
	Image.Good.Length = { 150, 50 };
	
	Image.Miss.Content = "Miss";
	Image.Miss.Location = { 100, -130 };
	Image.Miss.Length = { 150, 50 };

	Image.Rank.Content = ConstValue::RankToImg.at(pResult->Rank).data();
	Image.Rank.Location = { 100, 130 };
	Image.Rank.Length = { 50, 50 };

	//텍스트 셋팅
	Text.Title.Content = pSong->STR.Title.data();
	Text.Title.Location = { 640,  640 };
	Text.Title.Font = { "CookieRun Bold", 45, true };
	Text.Title.Length = { 500, 100 };
	Text.Title.Color = { 255, 255, 255 };

	Text.IndiCombo.Content = "Max Combo : ";
	Text.IndiCombo.Location = { 740,  350 };
	Text.IndiCombo.Font = { "CookieRun Bold", 30, true };
	Text.IndiCombo.Length = { 300, 100 };
	Text.IndiCombo.Color = { 255, 255, 255 };

	Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).data();
	Text.Diff.Location = { 645,  675 };
	Text.Diff.Font = { "CookieRun Bold", 30, true };
	Text.Diff.Length = { 120, 50 };
	Text.Diff.Color = { 255, 255, 255 };

	Text.BestScore.Content = pResult->STR.Score.data();
	Text.BestScore.Location = { 1000, 250 };
	Text.BestScore.Length = { 500, 100 };
	Text.BestScore.Font = { "CookieRun Regular", 50, true };
	Text.BestScore.Color = { 255, 255, 255 };

	Text.MaxCombo.Content = pResult->STR.MaxCombo.data();
	Text.MaxCombo.Location = { 1000, 350 };
	Text.MaxCombo.Length = { 300, 100 };
	Text.MaxCombo.Font = { "CookieRun Regular", 30, true };
	Text.MaxCombo.Color = { 255, 255,255 };

	Text.Perfect.Content = pResult->STR.Perfect.data();
	Text.Perfect.Location = { 1000, 400 };
	Text.Perfect.Length = { 300, 50 };
	Text.Perfect.Font = { "CookieRun Regular", 30, true };
	Text.Perfect.Color = { 255, 255, 255 };

	Text.Good.Content = pResult->STR.Good.data();
	Text.Good.Location = { 1000, 450 };
	Text.Good.Length = { 300, 50 };
	Text.Good.Font = { "CookieRun Regular", 30, true };
	Text.Good.Color = { 255, 255, 255 };

	Text.Miss.Content = pResult->STR.Miss.data();
	Text.Miss.Location = { 1000, 500 };
	Text.Miss.Length = { 300, 50 };
	Text.Miss.Font = { "CookieRun Regular", 30, true };
	Text.Miss.Color = { 255, 255, 255 };
}

bool ResultScene::Update()
{
	Camera.Set();
	Background.Draw();

	Image.Perfect.Draw();
	Image.Good.Draw();
	Image.Miss.Draw();
	Image.Thumbnail.Draw();
	Image.VLine.Draw();
	Image.Rank.Draw();

	Text.IndiCombo.Draw();
	Text.Diff.Draw();
	Text.Title.Draw();
	
	Text.BestScore.Draw();
	Text.MaxCombo.Draw();
	Text.Perfect.Draw();
	Text.Good.Draw();
	Text.Miss.Draw();

	if (Input::Get::Key::Down(VK_RETURN) || Input::Get::Key::Down(VK_ESCAPE)) return true;
	return false;
}