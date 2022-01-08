#pragma once
#include "ModeScenes.h"
#include "JudgePhrase.h"
#include "HitEffect.h"
#include "Component/Note.h"
#include "Component/Chart.h"

class PlayScene final : public ModeScenes
{
private:
	size_t keys[4];
	std::vector<Note> Notes[4];
	UINT nextNodeIndex[4] = { 0, 0, 0, 0 };
	size_t noteCount[4] = { 0, 0, 0, 0 };
	JudgePhrase* judgePhrase;
	HitEffect *hitEffects[4];
	float timed = 0.0f;

	Rendering::Camera               Camera;
	Rendering::Image::Component		Lane;
	Rendering::Image::Component     Background;

public:
	void Start(GeneralSetting *&generalSetting)  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};