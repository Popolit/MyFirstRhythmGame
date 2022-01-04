#pragma once
#include "Manager/Scene.h"

class TitleScene : public Scene
{
public:
	void Start()  override;
	bool Update() override;
	void End()    override;

private:
	Rendering::Camera               Camera;

	Rendering::Image::Component     Background;

	Rendering::Animation::Component SelectArrow;

	Rendering::Text::Component StartGame;
	Rendering::Text::Component Option;
	Rendering::Text::Component EndGame;
};


