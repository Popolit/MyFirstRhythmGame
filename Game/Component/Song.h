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

	Rendering::Text::Component		Title;
	Rendering::Text::Component		Artist;
	Rendering::Text::Component		MaxScore;

public:
	Song();
	Song(std::string const& file);
	void ParseData(std::string& data);
	void SetCenter();
	void UnsetCenter();
	std::string GetTitle();
	UINT GetHighlight();
};

