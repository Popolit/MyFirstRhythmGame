#pragma once
#include "ModeScenes.h"

class TitleScene final : public ModeScenes
{
private:
	ConstValue::SceneList Selection;

	Rendering::Camera               Camera;

	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectMode;

	Rendering::Text::Component StartGame;
	Rendering::Text::Component Option;
	Rendering::Text::Component EndGame;
public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};


