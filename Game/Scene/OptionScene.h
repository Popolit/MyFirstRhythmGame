#pragma once
#include "ModeScenes.h"
class OptionScene final : public ModeScenes
{
private:
	size_t keys[4];
	int SyncValue;
	float Speed;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	Rendering::Text::Component		textSync;
	Rendering::Text::Component		textSpeed;
	Rendering::Text::Component		textKeys[4];
public:
	void Start(GeneralSetting*& generalSetting)  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};