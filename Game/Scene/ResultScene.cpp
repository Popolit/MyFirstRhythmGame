#include "stdafx.h"
#include "ResultScene.h"

ResultScene::ResultScene(bool const& isNewResult)
{
	SM = SoundManager::Get();
	pSong = Resource::Get::NowPlaying();

	STR.Title = pSong->STR.Title.data();

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

	Text.Title.Content = STR.Title.data();
	Text.Title.Location = { 640,  640 };
	Text.Title.Font = { "CookieRun Bold", 45, true };
	Text.Title.Length = { 500, 100 };
	Text.Title.Color = { 255, 255, 255 };

	Text.Combo.Content = "Max Combo : ";
	Text.Combo.Location = { 740,  350 };
	Text.Combo.Font = { "CookieRun Bold", 30, true };
	Text.Combo.Length = { 300, 100 };
	Text.Combo.Color = { 255, 255, 255 };

	Text.Diff.Content = ConstValue::DiffToStr.at(Resource::Get::Diff()).data();
	Text.Diff.Location = { 645,  675 };
	Text.Diff.Font = { "CookieRun Bold", 30, true };
	Text.Diff.Length = { 120, 50 };
	Text.Diff.Color = { 255, 255, 255 };

	if (isNewResult)
	{
		pResult = Resource::Get::NowResult();
		pSong->ResultUpdate(pResult);
		delete pResult;
	}
	pResult = pSong->BestResults[static_cast<int>(Resource::Get::Diff())];
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

	Text.Combo.Draw();
	Text.Diff.Draw();
	Text.Title.Draw();
	pResult->Draw();


	if (Input::Get::Key::Down(VK_RETURN) || Input::Get::Key::Down(VK_ESCAPE)) return true;
	return false;
}