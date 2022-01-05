#pragma once
#include "GeneralSetting.h"
#include "Engine/Game.h"

class Game final : public Engine::Game
{
public:
	void Start() override;
	bool Update() override;
	void End() override;

public:
	std::vector<class Scene*> Scenes;
	GeneralSetting *generalSetting = new GeneralSetting();
	UINT Now = 0;
};
