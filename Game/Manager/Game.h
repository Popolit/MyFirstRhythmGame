#pragma once
#include "Engine/Game.h"
#include "Resource.h"
#include "ConstValue.h"

class Game final : public Engine::Game
{
public:
	void Start()override;
	bool Update() override;
	void End() override;

public:
	std::map<ConstValue::SceneList, class ModeScenes*> Scenes;
	ConstValue::SceneList NowScene;
};
