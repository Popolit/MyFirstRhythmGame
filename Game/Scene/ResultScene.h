#pragma once
#include "Manager/Result.h"
#include "Component/Song.h"

class ResultScene final
{
private:
	SoundManager* SM;
	Sound::Sound BGM;
	Song* pSong;
	Result* pResult;


	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	struct
	{
		Rendering::Text::Component	Perfect;
		Rendering::Text::Component	Good;
		Rendering::Text::Component	Miss;
		Rendering::Text::Component  Title;
		Rendering::Text::Component	Artist;
		Rendering::Text::Component	BestScore;

		Rendering::Text::Component  Diff;
		Rendering::Text::Component  IndiCombo;
		Rendering::Text::Component  MaxCombo;

	}Text;

	struct
	{
		Rendering::Image::Component	Thumbnail;
		Rendering::Image::Component	VLine;

		Rendering::Image::Component	Perfect;
		Rendering::Image::Component	Good;
		Rendering::Image::Component	Miss;

		Rendering::Image::Component Rank;
	}Image;


public:
	ResultScene(bool const& isNewResult = true);
	bool Update();
};

