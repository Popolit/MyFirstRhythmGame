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
	if(prev != SceneList::End) Now = Scenes.at(static_cast<int>(Now))->UpdateScene();

	if (Now == SceneList::End)
	{
		Now = prev;
		return true;
	}
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
	Scenes.at(static_cast<int>(Now))->End();
	for (ModeScenes* scene : Scenes)
	{
		delete scene;
	}
}

Engine::Game* Engine::Initialize() {return new::Game();}