//���� �ϳ��� �����͸� �о�� ���̺귯��
#include <filesystem>
#include "Resource.h"

void Resource::Import(std::string const directory, void (* const function)(std::string const& file))
{
	using namespace std::filesystem;
	if (exists(directory))
	{
		for(path const &path : recursive_directory_iterator(directory))	//recursive = ���� �� ������ ��� ����
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