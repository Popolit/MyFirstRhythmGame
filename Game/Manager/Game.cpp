#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/OptionScene.h"
#include "Scene/SelectSongScene.h"
#include "Scene/PlayScene.h"

void Game::Start()
{
	GameValue::Start();
	Now = ConstValue::SceneList::Title;

	Scenes.push_back(new TitleScene);
	Scenes.push_back(new PlayScene);
	Scenes.push_back(new SelectSongScene);
	Scenes.push_back(new OptionScene);

	Scenes.at(0)->Start();
}
bool Game::Update()
{
	using namespace ConstValue;
	SceneList prev = Now;
	Now = Scenes.at(static_cast<int>(Now))->UpdateScene();

	if (Now == SceneList::End) return true;
	if (Now != prev)
	{
		if (Now == SceneList::SelectSong) Now = SceneList::Play;
		Scenes.at(static_cast<int>(prev))->End();
		Scenes.at(static_cast<int>(Now))->Start();
	}

	return false;
}
void Game::End()
{
	for (Scene* scene : Scenes)
	{
		scene->End();
		delete scene;
	}
}

Engine::Game* Engine::Initialize() {return new::Game();}