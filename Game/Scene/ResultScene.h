#pragma once
#include "ModeScenes.h"
#include "Manager/Result.h"
#include "Component/Song.h"

class ResultScene final : public ModeScenes
{
private:
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
		Rendering::Text::Component  Diff;
		Rendering::Text::Component  Combo;
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
	Song* pSong;
	Result* pResult;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};

