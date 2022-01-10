#pragma once
#include "ModeScenes.h"
#include "Manager/ConstValue.h"
#include <string>
#include "Manager/Keycode.h"
class OptionScene final : public ModeScenes
{
private:
	int SyncValue;
	float SpeedValue;
	size_t Keys[4];
	UINT KeyIndex = 0;
	bool IsSelected = false;
	bool IsSettingChanged;

	ConstValue::OptionList Selection;
	void* Indicate = &SyncValue;
	
	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Image::Component		OptionUnderLine;
	Rendering::Image::Component		KeysBox[4];

	Rendering::Text::Component		OptionText;

	Rendering::Text::Component		IndiSync;
	Rendering::Text::Component		IndiSpeed;
	Rendering::Text::Component		IndiKeys;

	Rendering::Text::Component		TextSyncValue;
	Rendering::Text::Component		TextSpeedValue;
	Rendering::Text::Component		TextKeys[4];

	Rendering::Animation::Component AnimSelect;

public:
	void Start(GeneralSetting*& generalSetting)  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};