#include "stdafx.h"
#include "Resource.h"
#include "Component/Chart.h"
#include "Component/Song.h"

namespace Resource
{
	namespace 
	{
		//옵션
		int SyncValue = int();
		float SpeedValue = float();
		size_t MappedKeys[4] = { 0, };

		//공용 자원
		std::vector<class Song*> Songs;
		size_t SongSize;
		SoundManager *SM;
		std::string BGMTitle;
		class Chart* pCh = nullptr;
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

		SM = new SoundManager();
		SM->SetVolume(DefVolume);
		SM->SetBGM("TitleBGM");

		GetSongs();
		SongSize = Songs.size();
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

	void End() { delete pCh; delete SM; }


	namespace Get
	{
		int SyncValue() { return Resource::SyncValue; }
		float SpeedValue() { return Resource::SpeedValue; }
		void Keys(size_t (&target)[4]) { for (UINT u = 0; u < 4; u++) target[u] = Resource::MappedKeys[u]; }
		const char* Title() { return BGMTitle.data(); }
		Song* SongAt(size_t& index) 
		{ 
			if (SongSize <= index) index -= SongSize;
			return Songs.at(index);
		}
		Chart *pChart() { return pCh; }
		SoundManager* SM() { return Resource::SM; }
	}
	namespace Set
	{
		void SyncValue(int const& newSync) { Resource::SyncValue = newSync; }
		void SpeedValue(float const& newSpeed) { Resource::SpeedValue = newSpeed; };
		void Keys(size_t (&newKeys)[4]) { for (UINT u = 0; u < 4; u++) Resource::MappedKeys[u] = newKeys[u]; }
		void pChart(Chart* ch) { memcpy(pCh, ch, sizeof(Chart)); };
		void BGM(std::string const& title) { BGMTitle = title; }
		void Volume(float const& volume) { SM->Volume = volume;}
	}
};