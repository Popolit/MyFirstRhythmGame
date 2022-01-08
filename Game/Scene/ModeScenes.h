#pragma once
#include "Manager/GeneralSetting.h"
#include "Manager/ConstValue.h"
#include "Manager/Scene.h"

class ModeScenes : public Scene
{
public:
	GeneralSetting *generalSetting;

public:
	void Start() {}
	virtual void Start(GeneralSetting*& generalSetting) abstract;
	void Update() {}
	virtual ConstValue::SceneList UpdateScene() abstract;
	virtual void PlaySong() abstract;
};

