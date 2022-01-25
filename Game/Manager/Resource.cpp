#include "stdafx.h"
#include "Resource.h"
#include "Component/Chart.h"
#include "Component/Song.h"
#include "Result.h"

namespace Resource
{
	namespace 
	{
		//옵션
		int SyncValue = int();
		float SpeedValue = float();
		size_t MappedKeys[4] = { 0, };

		//공용 자원
		std::string BGMTitle;
		std::vector<Song*> Songs;
		std::vector<Result*> Results;
		Song* NowPlaying;
		Result* NowResult;

		size_t SongCnt;
		ConstValue::Difficulty NowDiff;
	}

	void Start()
	{
		using namespace ConstValue;
		SyncValue = 0;
		SpeedValue = DefSpeed;
		MappedKeys[0] = DefKeys[0];
		MappedKeys[1] = DefKeys[1];
		MappedKeys[2] = DefKeys[2];
		MappedKeys[3] = DefKeys[3];

		GetSongs();
		SongCnt = Songs.size();
		NowPlaying = Songs.at(0);
		NowResult = nullptr;
		NowDiff = ConstValue::Difficulty::Easy;
	}

	// 데이터 폴더 탐색, 곡 데이터를 받아옴
	void GetSongs()
	{
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
					Songs.push_back(song);
				}
			}
		}
	}

	void End() 
	{
		delete NowResult;
		for(Song* song : Songs) delete song;
		for(Result*result : Results) delete result;
	}


	namespace Get
	{
		int SyncValue() { return Resource::SyncValue; }
		float SpeedValue() { return Resource::SpeedValue; }
		void Keys(size_t (&target)[4]) { for (UINT u = 0; u < 4; u++) target[u] = Resource::MappedKeys[u]; }
		int SongIndex() { return static_cast<int>(std::find(Songs.begin(), Songs.end(), Resource::NowPlaying) - Songs.begin()); }
		Song* NowPlaying() { return Resource::NowPlaying; }
		ConstValue::Difficulty Diff() { return NowDiff; }
		Result* NowResult() { return Resource::NowResult; }
	}
	namespace Set
	{
		void SyncValue(int const& newSync) { Resource::SyncValue = newSync; }
		void SpeedValue(float const& newSpeed) { Resource::SpeedValue = newSpeed; };
		void Keys(size_t (&newKeys)[4]) { for (UINT u = 0; u < 4; u++) Resource::MappedKeys[u] = newKeys[u]; }
		void BGM(std::string const& title) { BGMTitle = title; }
		void NowPlaying(int& index) 
		{
			if (index < 0) index += static_cast<int>(SongCnt);
			else if (SongCnt <= index) index -= static_cast<int>(SongCnt);
			Resource::NowPlaying = Songs.at(index);
		}
		void Diff(ConstValue::Difficulty const& diff) { NowDiff = diff; }
		void NowResult(Score* score, Combo* combo)
		{
			Resource::NowResult = new Result();
			Resource::NowResult->Set(score, combo);
		}
	}
};