#include "stdafx.h"
#include "Song.h"

Song::Song() {}

Song::Song(std::string const& file)
{
	//파일을 입력받음
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
	ParseData(data);

	Thumbnail.Content = STR.Title.data();
	Thumbnail.Length = { 400, 400 };
	Thumbnail.Location = { -200, 0 };

	//텍스트 셋팅
	Title.Content = STR.Title.data();
	Title.Location = { 820,  220 };
	Title.Font = { "CookieRun Bold", 40, true };
	Title.Length = { 300, 100 };
	Title.Color = { 255, 255, 255 };

	Artist.Content = STR.Artist.data();
	Artist.Location = { 820,  320 };
	Artist.Font = { "CookieRun Bold", 40, true };
	Artist.Length = { 300, 100 };
	Artist.Color = { 255, 255, 255 };
}

//데이터 파싱
void Song::ParseData(std::string& data)
{
	size_t x = data.find_first_of('[');
	size_t y = data.find_first_of(']');
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

			pos = content.find_first_of(',');
			STR.Title = content.substr(0, pos);
			content.erase(0, pos + sizeof(char));
			while (content[0] == ' ') content.erase(0, 1);

			STR.Artist = content.substr(0, content.find_first_of(','));
			pos = content.find_first_of(',');
			content.erase(0, pos + sizeof(char));
			while (content[0] == ' ') content.erase(0, 1);

			Highlight = stoi(content);
		}
		//노트 데이터 파싱
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
}

Chart* Song::GetChart(ConstValue::Difficulty const& diff)
{
	using namespace ConstValue;
	switch (diff)
	{
		case Difficulty::Easy:
			return Easy;
		case Difficulty::Normal:
			return Normal;
		case Difficulty::Hard:
			return Hard;
	}
	return nullptr;
}


std::string Song::GetTitle()
{
	return STR.Title;
}

UINT Song::GetHighlight()
{
	return Highlight;
}

void Song::Draw()
{
	Thumbnail.Draw();
	Title.Draw();
	Artist.Draw();
}