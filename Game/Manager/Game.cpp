#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/SelectSongScene.h"
#include "Scene/OptionScene.h"
#include "Scene/PlayScene.h"
#include "Scene/ResultScene.h"

void Game::Start()
{
	Resource::Start();
	NowScene = ConstValue::SceneList::Title;

	Scenes.insert({ ConstValue::SceneList::Title, new TitleScene });
	Scenes.insert({ ConstValue::SceneList::SelectSong, new SelectSongScene });
	Scenes.insert({ ConstValue::SceneList::Option, new OptionScene });
	Scenes.insert({ ConstValue::SceneList::Play, new PlayScene });
	Scenes.insert({ ConstValue::SceneList::Result, new ResultScene });

	Scenes[NowScene]->Start();
}
bool Game::Update()
{
	using namespace ConstValue;
	SceneList prevScene = NowScene;
	NowScene = Scenes[prevScene]->Update();
	if (NowScene == SceneList::End)
	{
		NowScene = prevScene;
		return true;
	}
	if (NowScene != prevScene)
	{
		Scenes[prevScene]->End();
		Scenes[NowScene]->Start();
	}
	return false;
}
void Game::End()
{
	Scenes[NowScene]->End();
	for (auto it : Scenes)
	{
		delete it.second;
	}
	Resource::End();
}

Engine::Game* Engine::Initialize() {return new::Game();}