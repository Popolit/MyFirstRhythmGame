#pragma once
#include "Chart.h"

class Song
{
private:
	friend class SelectSongScene;
	friend class ResultScene;
	struct 
	{
		std::string Title;
		std::string Artist;
		std::string BestScore;
	}STR;

	//UINT Length;
	UINT Highlight;

	Chart *Easy;
	Chart *Normal;
	Chart *Hard;

public:
	Song();
	Song(std::string const& file);
	void ParseData(std::string& data);
	Chart* GetChart(ConstValue::Difficulty const&diff);
};

