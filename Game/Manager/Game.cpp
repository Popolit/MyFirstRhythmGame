#include "stdafx.h"
#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/SelectSongScene.h"
#include "Scene/OptionScene.h"
#include "Scene/PlayScene.h"

void Game::Start()
{
	Resource::Start();
	NowScene = ConstValue::SceneList::Title;

	Scenes.insert({ ConstValue::SceneList::Title, new TitleScene });
	Scenes.insert({ ConstValue::SceneList::SelectSong, new SelectSongScene });
	Scenes.insert({ ConstValue::SceneList::Option, new OptionScene });
	Scenes.insert({ ConstValue::SceneList::Play, new PlayScene });

	Scenes[NowScene]->Start();
}
bool Game::Update()
{
	using namespace ConstValue;
	SceneList prevScene = NowScene;
	NowScene = Scenes[prevScene]->Update();
	
	//게임 종료
	if (NowScene == SceneList::End)
	{
		NowScene = prevScene;
		return true;
	}
	//씬이 변경된 경우
	if (NowScene != prevScene)
	{
		Scenes[prevScene]->End();
		Scenes[NowScene]->Start();
	}
	return false;
}
void Game::End()
{
	//실행되던 씬을 종료 후 메모리 해제
	Scenes[NowScene]->End();
	for (std::pair<ConstValue::SceneList, Scene*> it : Scenes)
	{
		if (it.second != nullptr)
		{
			delete it.second;
			it.second = nullptr;
		}
	}
	Resource::End();
}

Engine::Game* Engine::Initialize() {return new::Game();}