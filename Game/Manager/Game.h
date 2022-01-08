#pragma once
#include "GeneralSetting.h"
#include "Engine/Game.h"
#include "ConstValue.h"

class Game final : public Engine::Game
{
public:
	void Start() override;
	bool Update() override;
	void End() override;

public:
	std::vector<class ModeScenes*> Scenes;
	GeneralSetting *generalSetting;
	ConstValue::SceneList Now;
};
