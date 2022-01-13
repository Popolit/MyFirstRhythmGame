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

	//Image 파일
	//Sound 파일
public:
	void Import(std::string const& name);
};

