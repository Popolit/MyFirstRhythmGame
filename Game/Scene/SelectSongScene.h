#pragma once
#include "ModeScenes.h"
class SelectSongScene final : public ModeScenes
{
private:
	ConstValue::SceneList Selection;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectionBox;

public:
	void Start(GeneralSetting*& generalSetting)  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};

