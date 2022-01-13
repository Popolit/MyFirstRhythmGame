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
	//TODO: ���̵� �߰� �ʿ�

	//pair<Ÿ�̹�, ��>
	std::vector<std::pair<UINT, UINT>> NoteData[4];
public:
	Chart() = default;
	Chart(std::string const& file)
	{
		//ä�� ���� �ε�
		FILE* chartFile = nullptr;
		const std::string directory = "Datas";
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
		std::string content;
		char buffer = ' ';
		while (buffer != EOF)
		{
			buffer = fgetc(chartFile);
			content += buffer;
		}

		

		//��Ÿ������ �Ľ�		
		content = content.substr(content.find_first_of("]") + sizeof(char) * 2);
		std::string metadata = content.substr(0, content.find_first_of("["));

		//TODO : �Ľ��ϱ�

		//��Ʈ ������ �Ľ�
		std::string notedata = content.substr(content.find_first_of("]") + sizeof(char) * 2);

		size_t pos = 0;
		while ((pos = notedata.find('\n')) != std::string::npos)
		{
			std::string ndata = notedata.substr(0, pos);
			int line = ndata[0] - '0';

			size_t x = ndata.find_first_of(',') + sizeof(char);
			size_t y = ndata.find_last_of(',');
			int timing = stoi(ndata.substr(x, y - x));
			int length = stoi(ndata.substr(y + sizeof(char)));

			NoteData[line].push_back({ timing, length});
			notedata.erase(0, pos + sizeof(char));
		}

		//����
		for (UINT u = 0; u < 4; u++) std::sort(NoteData[u].begin(), NoteData[u].end());
	}


	void makeNotes(std::vector<Note> (&Notes)[4])
	{
		int SyncValue = GameValue::Get::SyncValue();
		for (UINT u = 0; u < 4; u++)
		{
			for (std::pair<UINT, UINT> ndata : NoteData[u])
			{
				Note note = Note(ndata.first + SyncValue + 200);
				note.MakeNoteImage(u);
				Notes[u].push_back(note);
			}
		}
	}
};

