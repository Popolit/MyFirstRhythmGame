#pragma once
#include "Chart.h"

#include <string>
class Song
{
private:
	friend class SelectSongScene;

	std::string Title;
	std::string Artist;
	UINT BestScore;
	UINT Length;
	UINT Highlight;

	Chart *Easy;
	Chart *Normal;
	Chart *Hard;

	Sound::Sound song;
public:
	Song();
	Song(std::string const& file);
	void SetCenter();
	void UnsetCenter();
	std::string GetTitle();
};

