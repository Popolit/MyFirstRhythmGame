#pragma once
#include <string>


namespace Resource
{
	//2�� ���ڴ� �Լ�������
	void Import(std::string const directory, void (* const function)(std::string const &file));
}