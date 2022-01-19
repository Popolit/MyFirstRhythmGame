#pragma once
#include "ModeScenes.h"
#include "Manager/ConstValue.h"
#include <string>


class OptionScene final : public ModeScenes
{
private:
	struct final
	{
		std::string Sync;
		std::string Speed;
		std::string Volume;
		std::string Keys[4];
	}Str;

	UINT KeyIndex;
	size_t MappedKeys[4];
	bool IsSelected;
	ConstValue::OptionList Selection;
	
	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Image::Component		OptionUnderLine;
	Rendering::Image::Component		KeyBox[4];
	Rendering::Image::Component     ArrowUp;
	Rendering::Image::Component     ArrowDown;
	Rendering::Image::Component     ArrowSelection;

	Rendering::Text::Component		OptionText;

	Rendering::Text::Component		IndiSync;
	Rendering::Text::Component		IndiSpeed;
	Rendering::Text::Component		IndiKeys;

	Rendering::Text::Component		TextSyncValue;
	Rendering::Text::Component		TextSpeedValue;
	Rendering::Text::Component		TextKeys[4];

	Rendering::Animation::Component AnimSelect;
public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};