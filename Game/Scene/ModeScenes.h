#pragma once
#include "Manager/ConstValue.h"
#include "Manager/GameValue.h"
#include "Manager/Scene.h"

class ModeScenes : public Scene
{
public:
	void Update() {}
	virtual ConstValue::SceneList UpdateScene() abstract;
	virtual void PlaySong() abstract;
};

