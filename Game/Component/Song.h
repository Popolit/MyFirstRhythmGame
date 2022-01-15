#pragma once
#include <string>
class Song
{
protected:
	std::string Title;
	std::string Artist;
	UINT BestScore;
	UINT Length;
	UINT Highlight;

	Rendering::Image::Component Thumbnail;
	Sound::Sound song;
public:
	Song();
	Song(std::string const& file);
};

