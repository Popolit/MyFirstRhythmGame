//파일 하나의 데이터를 읽어내는 라이브러리
#include <filesystem>
#include "Resource.h"

void Resource::Import(std::string const directory, void (* const function)(std::string const& file))
{
	using namespace std::filesystem;
	if (exists(directory))
	{
		for(path const &path : recursive_directory_iterator(directory))	//recursive = 폴더 내 폴더도 모두 읽음
		{
			if (is_regular_file(path))
			{
				std::string file = path.string();
				std::replace(file.begin(), file.end(), '\\', '/');
				function(file);
			}
		}
	}
}