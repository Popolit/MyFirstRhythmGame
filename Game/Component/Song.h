#pragma once
#include "Chart.h"

class Song
{
private:
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

	Rendering::Image::Component		Thumbnail;
	Rendering::Image::Component		VLine;

	Rendering::Text::Component		Title;
	Rendering::Text::Component		Artist;
	Rendering::Text::Component		BestScore;

public:
	Song();
	Song(std::string const& file);
	void ParseData(std::string& data);
	Chart* GetChart(ConstValue::Difficulty const&diff);
	std::string GetTitle();
	UINT GetHighlight();
	void Draw();
	void DrawForResult();
};

