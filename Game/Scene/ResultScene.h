#pragma once
#include "Manager/Scene.h"
#include "Manager/Result.h"
#include "Component/Song.h"

class ResultScene final : public Scene
{
private:
	Sound::Sound BGM;
	Song* pSong;
	Result* pResult;


	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	struct 
	{
		std::string Perfect;
		std::string Good;
		std::string Miss;
		std::string Title;
	}STR;

	struct
	{
		Rendering::Text::Component	Perfect;
		Rendering::Text::Component	Good;
		Rendering::Text::Component	Miss;
		Rendering::Text::Component  Title;
		Rendering::Text::Component	Artist;
		Rendering::Text::Component	BestScore;

		Rendering::Text::Component  Diff;
		Rendering::Text::Component  Combo;

	}Text;

	struct
	{
		Rendering::Image::Component	Thumbnail;
		Rendering::Image::Component	VLine;

		Rendering::Image::Component	Perfect;
		Rendering::Image::Component	Good;
		Rendering::Image::Component	Miss;
	}Image;


public:
	void Start()  override;
	ConstValue::SceneList Update() override;
	void End()    override;
};

