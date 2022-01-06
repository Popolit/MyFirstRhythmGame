#pragma once
#include "ModeScenes.h"
#include "Component/Note.h"
#include "Component/Chart.h"

class PlayScene final : public ModeScenes
{
private:
	size_t keys[4];
	std::vector<Note> Notes[4];
	UINT nextNodeIndex[4] = { 0, 0, 0, 0 };
	size_t noteCount[4] = { 0, 0, 0, 0 };
	GeneralSetting* generalSetting;
	float timed = 0.0f;

	Rendering::Camera               Camera;
	Rendering::Image::Component		Lane;
	Rendering::Image::Component     Background;
	Rendering::Image::Component		JudgePhrase;

public:
	void Start(GeneralSetting *&generalSetting)  override;
	UINT Update() override;
	void End()    override;
	void PlaySong() override;
};