#include "stdafx.h"
#include "Song.h"

Song::Song()
{
	Thumbnail.Content = "NoImage";
	Thumbnail.Length = { 500, 500 };
	Thumbnail.Location = { 300, 300 };
}

Song::Song(std::string const& file)
{
	
}
