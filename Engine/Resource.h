#pragma once
#include <string>


namespace Resource
{
	//2번 인자는 함수포인터
	void Import(std::string const directory, void (* const function)(std::string const &file));
}