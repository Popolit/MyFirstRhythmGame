#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start()
{
	Selection = 0;

	Background.Content = "SelectSongBG1";
	Background.Length = { 1280, 720 };

	//데이터 파일 검색
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

	if (SongCount == 0) return;

	SongList.at(0)->SetCenter();

	Title.Content = SongList.at(0)->Title.data();
	Title.Location = { 820,  220 };
	Title.Font = { "CookieRun Bold", 40, true };
	Title.Length = { 300, 100 };
	Title.Color = { 255, 255, 255 };

	Artist.Content = SongList.at(0)->Artist.data();
	Artist.Location = { 820,  320 };
	Artist.Font = { "CookieRun Bold", 40, true };
	Artist.Length = { 300, 100 };
	Artist.Color = { 255, 255, 255 };

	Diff.Content = "Easy";
	Diff.Location = { 820,  420 };
	Diff.Font = { "CookieRun Bold", 40, true };
	Diff.Length = { 300, 100 };
	Diff.Color = { 255, 255, 255 };

	Thumbnail.Content = SongList.at(0)->Title.data();
	Thumbnail.Length = { 400, 400 };
	Thumbnail.Location = { -200, 0 };

	Difficulty = ConstValue::Difficulty::Easy;
	LoopLength = ConstValue::LoopLength;
	Volume = 0.0f;
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
	Song* selectedSong = SongList.at(Selection);
	//곡 변경
	if (Input::Get::Key::Down(VK_LEFT) && Selection < SongCount - 1)
	{
		Difficulty = ConstValue::Difficulty::Easy;
		selectedSong->UnsetCenter();
		Selection++;
		selectedSong = SongList.at(Selection);
		selectedSong->SetCenter();
		Volume = 0.0f;
		LoopLength = ConstValue::LoopLength;
	}
	if (Input::Get::Key::Down(VK_RIGHT) && 0 < Selection)
	{
		Difficulty = ConstValue::Difficulty::Easy;
		selectedSong->UnsetCenter();
		Selection--;
		selectedSong = SongList.at(Selection);
		selectedSong->SetCenter();
		Volume = 0.0f;
		LoopLength = ConstValue::LoopLength;
	}
	if (Input::Get::Key::Down(VK_UP))
	{
		++Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}
	if (Input::Get::Key::Down(VK_DOWN))
	{
		--Difficulty;
		Diff.Content = ConstValue::ToString(Difficulty).c_str();
	}


	StrTitle = selectedSong->Title;

	LoopLength -= Time::Get::Delta();
	if (selectedSong->song.isLoopEnd()) LoopLength = ConstValue::LoopLength;

	//곡이 끝나기 2초전 페이드아웃
	else if (LoopLength < 2.0f)
	{
		Volume -= Time::Get::Delta() / 20;
		selectedSong->song.volume = Volume;
		selectedSong->song.SetVolume();
	}
	//페이드 인
	else if (Volume < 0.1f)
	{
		Volume += Time::Get::Delta() / 20;
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
		GameValue::Set::pChart(selectedSong->Normal);
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

void SelectSongScene::PlaySong() { }