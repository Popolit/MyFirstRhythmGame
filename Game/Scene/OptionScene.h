#pragma once
#include "ModeScenes.h"
#include "Manager/ConstValue.h"
#include <string>
#include "Manager/Keycode.h"
class OptionScene final : public ModeScenes
{
private:
	ConstValue::OptionList Selection;
	size_t Keys[4];
	int SyncValue;
	float Speed;

	std::map <ConstValue::OptionList, Rendering::Text::Component> A;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Image::Component		OptionUnderLine;

	


	Rendering::Text::Component		OptionText;

	Rendering::Text::Component		TextSync;
	Rendering::Text::Component		TextSpeed;
	Rendering::Text::Component		TextKeys;

	Rendering::Text::Component		CurrentSync;
	Rendering::Text::Component		CurrentSpeed;
	Rendering::Text::Component		CurrentKeys[4];


public:
	void Start(GeneralSetting*& generalSetting)  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};