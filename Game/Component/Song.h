#pragma once
#include <string>
class Song
{
private:
	std::string Name;
	std::string Artist;
	UINT BestScore;
	UINT Length;
	UINT Highlight;

	//Image ����
	//Sound ����
public:
	void Import(std::string const& name);
};

