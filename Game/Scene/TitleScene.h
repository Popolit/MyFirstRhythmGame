#pragma once
#include "ModeScenes.h"

class TitleScene final : public ModeScenes
{
private:
	UINT Selection = 0;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectMode;

	Rendering::Text::Component StartGame;
	Rendering::Text::Component Option;
	Rendering::Text::Component EndGame;


public:
	void Start(GeneralSetting *&generalSetting)  override;
	UINT Update() override;
	void End()    override;
	void PlaySong() override;

};


