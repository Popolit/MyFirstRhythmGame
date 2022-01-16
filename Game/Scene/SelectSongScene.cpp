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

	Thumbnail.Content = SongList.at(0)->Title.data();
	Thumbnail.Length = { 400, 400 };
	Thumbnail.Location = { -200, 0 };

	Difficulty = ConstValue::Difficulty::Easy;
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
	if (Input::Get::Key::Down(VK_LEFT) && Selection < SongCount - 1)
	{
		Difficulty = ConstValue::Difficulty::Easy;
		SongList.at(Selection)->UnsetCenter();
		Selection++;
		SongList.at(Selection)->SetCenter();
		StrTitle = SongList.at(Selection)->GetTitle();
	}
	if (Input::Get::Key::Down(VK_RIGHT) && 0 < Selection)
	{
		Difficulty = ConstValue::Difficulty::Easy;
		SongList.at(Selection)->UnsetCenter();
		Selection--;
		SongList.at(Selection)->SetCenter();
		StrTitle = SongList.at(Selection)->GetTitle();
	}

	if (Input::Get::Key::Down(VK_UP)) ++Difficulty;
	if (Input::Get::Key::Down(VK_DOWN)) --Difficulty;
	

	Camera.Set();
	Background.Draw();
	Thumbnail.Draw();
	Title.Draw();
	Artist.Draw();


	if (Input::Get::Key::Down(VK_RETURN))
	{
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