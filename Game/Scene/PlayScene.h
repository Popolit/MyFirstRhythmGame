#pragma once
#include "ModeScenes.h"
#include "Component/Note.h"

class PlayScene final : public ModeScenes
{
private:
	size_t keys[4];
	std::vector<Note> Notes[4];
	
	
	Rendering::Camera               Camera;
	Rendering::Image::Component		Lane;
	Rendering::Image::Component     Background;

public:
	void Start(GeneralSetting *&generalSetting)  override;
	UINT Update() override;
	void End()    override;
	void PlaySong() override;
};