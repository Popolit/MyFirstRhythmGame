#include "stdafx.h"
#include "Song.h"

Song::Song() {}

Song::Song(std::string const& file)
{
	size_t x = file.find_first_of('/') + sizeof(char);
	size_t y = file.find_last_of('.');

	FILE* pFile = nullptr;
	fopen_s(&pFile, file.data(), "r");

	std::string data = "";
	char buffer = ' ';
	while (buffer != EOF)
	{
		buffer = fgetc(pFile);
		data += buffer;
	};

	x = data.find_first_of('[');
	y = data.find_first_of(']');
	while (y != std::string::npos)
	{
		//데이터 구분
		std::string classification = data.substr(x + sizeof(char), y - x - sizeof(char)).c_str();
		data.erase(0, y + sizeof(char) * 2);

		x = data.find_first_of('[');

		std::string content = data.substr(0, x - sizeof(char) * 2);
		data.erase(0, x);

		x = 0;
		y = data.find_first_of(']');

		//메타데이터 파싱		
		if (classification == "Metadata")
		{
			size_t pos = 0;
			content = content.substr(0, content.find_first_of('\n'));
			content.erase(std::remove(content.begin(), content.end(), ' '), content.end());

			pos = content.find_first_of(',');
			Title = content.substr(0, pos);
			content.erase(0, pos + sizeof(char));

			Artist = content.substr(0, content.find_first_of(','));
			pos = content.find_first_of(',');
			content.erase(0, pos + sizeof(char));

			Highlight = stoi(content);
		}
		else if (classification == "Notes")
		{
			size_t nx = content.find_first_of('#');
			size_t ny = content.find_first_of(':');

			while (ny != std::string::npos)
			{
				std::string level = content.substr(nx + sizeof(char), ny - nx - sizeof(char));
				content.erase(0, ny + 2 * sizeof(char));

				nx = content.find_first_of('#');

				std::string chartData = content.substr(0, nx - sizeof(char));
				content.erase(0, nx);

				nx = 0;
				ny = content.find_first_of(':');
				if (level == "Easy")
				{
					Easy = new Chart(chartData);
				}
				else if (level == "Normal")
				{
					Normal = new Chart(chartData);
				}
				else if (level == "Hard")
				{
					Hard = new Chart(chartData);
				}
			}
		}
	}

	song.Content = Title.c_str();
}

void Song::SetCenter()
{
	song.Set(true, Highlight);
	song.Play();
}

void Song::UnsetCenter()
{
	song.Stop();
}

std::string Song::GetTitle()
{
	return Title;
}