#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"

void Game::Start()
{
	Scenes.push_back(new TitleScene);

	Scenes.at(Now)->Start();
}
bool Game::Update()
{
	if (Scenes.at(Now)->Update())
	{
		if (++Now < Scenes.size())
		{
			Scenes.at(Now)->Start();
		}
	}
	return false;
}
void Game::End()
{
	for (Scene const* const scene : Scenes) delete scene;
}

Engine::Game* Engine::Initialize() {return new::Game();}