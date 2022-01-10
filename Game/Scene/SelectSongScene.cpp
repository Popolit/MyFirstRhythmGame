#include "stdafx.h"
#include "SelectSongScene.h"

void SelectSongScene::Start(GeneralSetting*& generalSetting)
{
}

ConstValue::SceneList SelectSongScene::UpdateScene()
{
    return ConstValue::SceneList::SelectSong;
}

void SelectSongScene::End() { }

void SelectSongScene::PlaySong() { }