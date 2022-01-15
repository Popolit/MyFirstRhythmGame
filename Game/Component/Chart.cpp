#include "stdafx.h"
#include "Chart.h"

Chart::Chart() : Song() {}

Chart::Chart(std::string const& file) : Song(file)
{
	//채보 파일 로딩
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

				//txt 형식만 받음
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

	//메타데이터 파싱		
	content = content.substr(content.find_first_of("]") + sizeof(char) * 2);
	std::string metadata = content.substr(0, content.find_first_of("["));

	size_t pos = 0;
	metadata = metadata.substr(0, metadata.find_first_of('\n'));
	metadata.erase(std::remove(metadata.begin(), metadata.end(), ' '), metadata.end());

	pos = metadata.find_first_of(',');
	Title = metadata.substr(0, pos);
	metadata.erase(0, pos + sizeof(char));

	Artist = metadata.substr(0, metadata.find_first_of(','));
	pos = metadata.find_first_of(',');
	metadata.erase(0, pos + sizeof(char));

	Highlight = stoi(metadata);

	//노트 데이터 파싱
	std::string notedata = content.substr(content.find_first_of("]") + sizeof(char) * 2);

	pos = 0;
	while ((pos = notedata.find('\n')) != std::string::npos)
	{
		std::string ndata = notedata.substr(0, pos);
		int line = ndata[0] - '0';

		size_t x = ndata.find_first_of(',') + sizeof(char);
		size_t y = ndata.find_last_of(',');
		int timing = stoi(ndata.substr(x, y - x));
		int length = stoi(ndata.substr(y + sizeof(char)));

		NoteData[line].push_back({ timing, length });
		notedata.erase(0, pos + sizeof(char));
	}

	//정렬
	for (UINT u = 0; u < 4; u++) std::sort(NoteData[u].begin(), NoteData[u].end());
}

void Chart::makeNotes(std::vector<Note>(&Notes)[4])
{
	int SyncValue = GameValue::Get::SyncValue();
	for (UINT u = 0; u < 4; u++)
	{
		for (std::pair<UINT, UINT> ndata : NoteData[u])
		{
			Note note = Note(ndata.first + SyncValue);
			note.MakeNoteImage(u);
			Notes[u].push_back(note);
		}
	}
}