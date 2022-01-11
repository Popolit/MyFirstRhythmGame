#pragma once
#include "Note.h"
#include "Manager/GameValue.h"
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

class Chart
{
private:
	std::vector<UINT> Timings[4];
public:
	Chart() = default;
	Chart(std::string const& file)
	{
		//ä�� ���� �ε�
		FILE* chartFile = nullptr;
		const std::string directory = "Songs";
		using namespace std::filesystem;
		if (exists(directory))
		{
			for (path const& path : directory_iterator(directory))
			{
				if (is_regular_file(path))
				{
					std::string file = path.string();

					//txt ���ĸ� ����
					if (file.substr(file.find_last_of('.') + sizeof(char)) != "txt") continue;
					std::replace(file.begin(), file.end(), '\\', '/');
					fopen_s(&chartFile, file.data(), "r");
					break;
				}
			}
		}

		//�Ľ�
		std::string Timing = "";
		UINT u = 0;
		char buffer = ' ';
		while (buffer != EOF)
		{
			buffer = fgetc(chartFile);
			//if(3 < u) ä���� �������� ���߽��ϴ�.;

			switch (buffer)
			{
				case '[': break;
				case ',':
				{
					Timings[u].push_back(stoi(Timing));
					Timing = "";
					break;
				}
				case ']':
				{
					Timings[u].push_back(stoi(Timing));
					Timing = "";
					u++;
					break;
				}
				default:
				{
					Timing += buffer;
					break;
				}
			}
		}

		//����
		for (UINT u = 0; u < 4; u++) std::sort(Timings[u].begin(), Timings[u].end());
	}


	void makeNotes(std::vector<Note> (&Notes)[4])
	{
		int SyncValue = GameValue::Get::SyncValue();
		for (UINT u = 0; u < 4; u++)
		{
			for (UINT Timing : Timings[u])
			{
				Note note = Note(Timing + SyncValue);
				note.MakeNoteImage(u);
				Notes[u].push_back(note);
			}
		}
	}
};

