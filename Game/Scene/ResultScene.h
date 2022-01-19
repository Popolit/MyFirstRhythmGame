#pragma once
#include "ModeScenes.h"
class ResultScene final : public ModeScenes
{
private:
	ConstValue::SceneList Selection;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectMode;

	Rendering::Text::Component StartGame;
	Rendering::Text::Component Option;
	Rendering::Text::Component EndGame;

	Sound::Sound BGM;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};

