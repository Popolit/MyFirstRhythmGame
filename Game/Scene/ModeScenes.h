#pragma once
#include "Manager/ConstValue.h"
#include "Manager/Resource.h"
#include "Manager/Scene.h"

class ModeScenes : public Scene
{
protected:
	SoundManager* SM;
public:
	void Update() {}
	virtual ConstValue::SceneList UpdateScene() abstract;
};

