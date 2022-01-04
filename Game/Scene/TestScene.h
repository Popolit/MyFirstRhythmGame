#pragma once
#include "Manager/Scene.h"

class TestScene final : public Scene
{
public:
	void Start()  override;
	bool Update() override;
	void End()    override;

private:
	Rendering::Camera               Camera;

	Rendering::Image::Component     Background;

	Rendering::Animation::Component Player;
};

