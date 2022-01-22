#pragma once
#include "ModeScenes.h"
class ResultScene final : public ModeScenes
{
private:
	ConstValue::SceneList Selection;

	struct 
	{
		std::string Perfect;
		std::string Good;
		std::string Miss;
	}Count;

	struct
	{
		Rendering::Text::Component	Perfect;
		Rendering::Text::Component	Good;
		Rendering::Text::Component	Miss;
	}Text;

	struct
	{
		Rendering::Image::Component	Perfect;
		Rendering::Image::Component	Good;
		Rendering::Image::Component	Miss;
	}Image;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	Sound::Sound BGM;
	Song* NowPlaying;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};

