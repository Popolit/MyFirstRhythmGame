#include "stdafx.h"
#include "Parser.h"

//파싱을 담당
namespace Parser
{
	//파일 데이터 파싱
	//포맷 예시 :
	// "[카테고리]"
	// "#내용: 값"
	map<string, map<string, string>> Parse(FILE *pFile)
	{
		map<string, map<string, string>> ret;

		std::string data = "";
		char buffer = fgetc(pFile);
		while (buffer != EOF)
		{
			data += buffer;
			buffer = fgetc(pFile);
		}

		size_t x = data.find('[') + sizeof(char);
		size_t y = y = data.find(']');
		while (y != string::npos)
		{	
			string category = data.substr(x, y - x);
			data.erase(0, y + 2 * sizeof(char));

			x = data.find('[');
			string content = data.substr(0, x - 2 * sizeof(char));
			data.erase(0, x - 2 * sizeof(char));

			map<string, string> contentMap;
			while (y != string::npos)
			{
				x = content.find('#') + sizeof(char);
				y = content.find(':');

				string subCategory = content.substr(x, y - x);
				content.erase(0, y + sizeof(char));

				y = content.find("#");
				string subContent = content.substr(1, y - 2 * sizeof(char));
				content.erase(0, y - sizeof(char));

				contentMap.insert({ subCategory, subContent });
			}
			x = data.find('[') + sizeof(char);
			y = y = data.find(']');

			ret.insert({ category, contentMap });
		}

		fclose(pFile);

		return ret;
	}
}