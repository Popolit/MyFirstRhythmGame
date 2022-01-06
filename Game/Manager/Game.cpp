#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/PlayScene.h"

void Game::Start()
{
	Scenes.push_back(new TitleScene);
	Scenes.push_back(new PlayScene);
	Scenes.at(Now)->Start(generalSetting);
}
bool Game::Update()
{
	UINT prev = Now;
	Now = Scenes.at(Now)->Update();

	if (Now != prev)
	{
		Scenes.at(prev)->End();
		Scenes.at(Now)->Start(generalSetting);
	}

	return false;
}
void Game::End()
{
	delete generalSetting;
	for (Scene const* const scene : Scenes) delete scene;
}

Engine::Game* Engine::Initialize() {return new::Game();}