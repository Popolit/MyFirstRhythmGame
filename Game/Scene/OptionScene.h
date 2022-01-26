#pragma once
#include "Manager/Scene.h"

class OptionScene final : public Scene
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

	struct
	{
		Rendering::Image::Component		UnderLine;
		Rendering::Image::Component		KeyBox[4];
		Rendering::Image::Component     ArrowUp;
		Rendering::Image::Component     ArrowDown;
		Rendering::Image::Component     ArrowSelection;
	}Image;
	
	struct
	{
		Rendering::Text::Component		Option;

		Rendering::Text::Component		IndiSync;
		Rendering::Text::Component		IndiSpeed;
		Rendering::Text::Component		IndiVolume;
		Rendering::Text::Component		IndiKeys;
		

		Rendering::Text::Component		SyncValue;
		Rendering::Text::Component		SpeedValue;
		Rendering::Text::Component		VolumeValue;
		Rendering::Text::Component		Keys[4];
	}Text;
	

	Rendering::Animation::Component AnimSelect;
public:
	void Start()  override;
	ConstValue::SceneList Update() override;
	void End()    override;
};