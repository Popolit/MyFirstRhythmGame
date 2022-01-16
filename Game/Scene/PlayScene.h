#pragma once
#include "Combo.h"
#include "ModeScenes.h"
#include "JudgePhrase.h"
#include "HitEffect.h"
#include "Component/Note.h"
#include "Component/Chart.h"
#include "Component/Score.h"

class PlayScene final : public ModeScenes
{
private:
	float SpeedValue;
	size_t MappedKeys[4];
	std::vector<Note> Notes[4];
	UINT nextNoteIndex[4];
	size_t noteCount[4];
	Combo* CurrentCombo;	//pCombo ·Î °íÃÄ!
	Score* CurrentScore;
	JudgePhrase* judgePhrase;
	HitEffect *hitEffects[4];
	float timed;

	Rendering::Camera               Camera;
	Rendering::Image::Component		Lane;
	Rendering::Image::Component     Background;

	Sound::Sound					Song;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};