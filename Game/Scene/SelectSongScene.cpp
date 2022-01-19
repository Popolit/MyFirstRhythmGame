#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	//변수 셋팅
	Selection = 0;
	Difficulty = ConstValue::Difficulty::Easy;
	LoopLength = ConstValue::LoopLength;
	Volume = 0.0f;

	//데이터 폴더 탐색, 곡 데이터를 받아옴
	const std::string directory = "Datas";
	using namespace std::filesystem;
	if (exists(directory))
	{
		for (path const& path : directory_iterator(directory))
		{
			if (is_regular_file(path))
			{
				std::string file = path.string();

				//txt 형식만 받음
				if (file.substr(file.find_last_of('.') + sizeof(char)) != "txt") continue;
				std::replace(file.begin(), file.end(), '\\', '/');

				Song* song = new Song(file);
				SongList.push_back(song);
			}
		}
	}
	SongCount = SongList.size();

	//이미지 셋팅
	Background.Content = "SelectSongBG1";
	Background.Length = ConstValue::ScreenSize;

	if (SongCount == 0) return;

	Thumbnail.Content = SongList.at(Selection)->Title.data();
	Thumbnail.Length = { 400, 400 };
	Thumbnail.Location = { -200, 0 };

	SongList.at(Selection)->SetCenter();

	//텍스트 셋팅
	Title.Content = SongList.at(Selection)->Title.data();
	Title.Location = { 820,  220 };
	Title.Font = { "CookieRun Bold", 40, true };
	Title.Length = { 300, 100 };
	Title.Color = { 255, 255, 255 };

	Artist.Content = SongList.at(Selection)->Artist.data();
	Artist.Location = { 820,  320 };
	Artist.Font = { "CookieRun Bold", 40, true };
	Artist.Length = { 300, 100 };
	Artist.Color = { 255, 255, 255 };

	Diff.Content = "Easy";
	Diff.Location = { 820,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 300, 100 };
	Diff.Color = { 255, 255, 255 };
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
	Song* selectedSong = SongList.at(Selection);
	//곡 변경
	if (Input::Get::Key::Down(VK_LEFT) && 0 < Selection)
	{
		GameValue::PlaySEMove();
		Difficulty = ConstValue::Difficulty::Easy;
		selectedSong->UnsetCenter();
		Selection--;
		selectedSong = SongList.at(Selection);
		selectedSong->SetCenter();
		Volume = 0.0f;
		LoopLength = ConstValue::LoopLength;
		Title.Content = selectedSong->Title.data();
		Artist.Content = selectedSong->Artist.data();
		Thumbnail.Content = selectedSong->Title.data();
	}
	if (Input::Get::Key::Down(VK_RIGHT) && Selection < SongCount - 1)
	{
		GameValue::PlaySEMove();
		Difficulty = ConstValue::Difficulty::Easy;
		selectedSong->UnsetCenter();
		Selection++;
		selectedSong = SongList.at(Selection);
		selectedSong->SetCenter();
		Volume = 0.0f;
		LoopLength = ConstValue::LoopLength;
		Title.Content = selectedSong->Title.data();
		Artist.Content = selectedSong->Artist.data();
		Thumbnail.Content = selectedSong->Title.data();
	}
	if (Input::Get::Key::Down(VK_UP))
	{
		GameValue::PlaySEMove();
		++Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}
	if (Input::Get::Key::Down(VK_DOWN))
	{
		GameValue::PlaySEMove();
		--Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}


	StrTitle = selectedSong->Title;

	LoopLength -= Time::Get::Delta();
	if (selectedSong->song.isLoopEnd()) LoopLength = ConstValue::LoopLength;

	//곡이 끝나기 2초전 페이드아웃
	else if (LoopLength < 2.0f)
	{
		Volume -= GameValue::Get::Volume() * Time::Get::Delta() / 2;
		selectedSong->song.volume = Volume;
		selectedSong->song.SetVolume();
	}
	//페이드 인
	else if (Volume < GameValue::Get::Volume())
	{
		Volume += GameValue::Get::Volume() * Time::Get::Delta() / 2;
		selectedSong->song.volume = Volume;
		selectedSong->song.SetVolume();
	}
	Camera.Set();
	Background.Draw();
	Thumbnail.Draw();
	Title.Draw();
	Artist.Draw();
	Diff.Draw();


	if (Input::Get::Key::Down(VK_RETURN))
	{
		GameValue::PlaySEDecide();
		GameValue::Set::BGM(selectedSong->Title);
		switch (Difficulty)
		{
			case ConstValue::Difficulty::Easy:
			{
				GameValue::Set::pChart(selectedSong->Easy);
				break;
			}
			case ConstValue::Difficulty::Normal:
			{
				GameValue::Set::pChart(selectedSong->Normal);
				break;
			}
			case ConstValue::Difficulty::Hard:
			{
				GameValue::Set::pChart(selectedSong->Hard);
				break;
			}
		}
		return ConstValue::SceneList::Play;
	}
	if (Input::Get::Key::Down(VK_ESCAPE)) return ConstValue::SceneList::Title;
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End() 
{
	SongList.at(Selection)->UnsetCenter();
	for (Song const* song : SongList) delete song;
	SongList.clear();
}