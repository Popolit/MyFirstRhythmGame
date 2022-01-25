#pragma once
#include "Manager/Scene.h"

class TitleScene final : public Scene
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
	ConstValue::SceneList Update() override;
	void End()    override;
};


