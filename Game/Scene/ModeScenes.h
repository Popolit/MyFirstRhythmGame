#pragma once
#include "Manager/GeneralSetting.h"
#include "Manager/ConstValue.h"
#include "Manager/Scene.h"

class ModeScenes : public Scene
{
public:
	GeneralSetting generalSetting;
	ConstValue::SceneList nowScene = ConstValue::SceneList::Main;

public:
	void Start() override {};
	virtual void Start(GeneralSetting*& generalSetting) abstract;
	virtual void PlaySong() abstract;
};

