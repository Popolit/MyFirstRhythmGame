#pragma once
#include "Manager/Scene.h"

class TitleScene : public Scene
{
public:
	void Start()  override;
	bool Update() override;
	void End()    override;

private:
	UINT Selection = 0;

	Rendering::Camera               Camera;

	Rendering::Image::Component     Background;

	Rendering::Animation::Component SelectMode;

	Rendering::Text::Component StartGame;
	Rendering::Text::Component Option;
	Rendering::Text::Component EndGame;
};


