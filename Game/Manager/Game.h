#pragma once
#include "Engine/Game.h"
#include "GameValue.h"
#include "ConstValue.h"

class Game final : public Engine::Game
{
public:
	void Start()override;
	bool Update() override;
	void End() override;

public:
	std::vector<class ModeScenes*> Scenes;
	ConstValue::SceneList Now;
};
