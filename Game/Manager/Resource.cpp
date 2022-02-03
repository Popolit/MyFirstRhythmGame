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
		Song* NowPlaying;
		Result* NowResult;

		size_t SongCnt;
		ConstValue::Difficulty NowDiff;
	}

	void Start()
	{
		GetOption();
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
	
	void GetOption()
	{
		const char* path = "Datas/Option.ini";
		FILE* pFile = nullptr;
		fopen_s(&pFile, path, "r");

		//옵션 파일이 없으면 디폴트
		if (pFile == NULL)
		{
			SyncValue = 0;
			SpeedValue = ConstValue::DefSpeed;
			SoundManager::Get()->SetVolume(ConstValue::DefVolume);
			MappedKeys[0] = ConstValue::DefKeys[0];
			MappedKeys[1] = ConstValue::DefKeys[1];
			MappedKeys[2] = ConstValue::DefKeys[2];
			MappedKeys[3] = ConstValue::DefKeys[3];
			fclose(pFile);
			return;
		}

		std::map<std::string, std::string> options = Parser::Parse(pFile)["Option"];

		SyncValue = stoi(options["Sync"]);
		SpeedValue = stof(options["Speed"]);
		SoundManager::Get()->SetVolume(stoi(options["Volume"]));

		std::string strKeys = options["Keys"];
		for (UINT u = 0; u < 4; u++)
		{
			size_t token = strKeys.find_first_of(',');
			MappedKeys[u] = stoi(strKeys.substr(0, token));
			strKeys.erase(0, token + sizeof(char));
		}	
	}

	void SaveOption()
	{
		using namespace std;

		const char* path = "Datas/Option.ini";
		FILE* pFile = nullptr;
		fopen_s(&pFile, path, "w");

		string data = "[Option]";
		data += "\n#Sync: ";
		data += to_string(SyncValue);
		data += "\n#Speed: ";
		string temp_speed = to_string(SpeedValue);
		data += temp_speed.substr(0, temp_speed.find_first_of('.') + 2 * sizeof(char));;
		data += "\n#Volume: ";
		data += to_string(static_cast<UINT>(round(SoundManager::Get()->Volume * 100)));
		data += "\n#Keys: ";
		for (UINT u = 0; u < 4; u++)
		{
			data += to_string(MappedKeys[u]);
			data += ", ";
		}
		data.pop_back();
		data.pop_back();

		fputs(data.data(), pFile);

		fclose(pFile);
	}

	void End() 
	{
		SaveOption();
		for(Song* song : Songs) delete song;
		SoundManager::Destroy();
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
		void NowResult(Result* result) { Resource::NowResult = result; }
	}
};