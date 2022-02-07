#pragma once
#include "Manager/Scene.h"
#include "ResultScene.h"
#include "Component/Combo.h"
#include "Component/JudgePhrase.h"
#include "Component/HitEffect.h"
#include "Component/Keybeam.h"
#include "Component/Note.h"
#include "Component/Song.h"
#include "Component/Score.h"

class PlayScene final : public Scene
{
private:
	Song* pSong;
	Combo* pCombo;
	Score* pScore;
	JudgePhrase* pJudgePhrase;
	HitEffect* pHitEffects[4];
	Keybeam* pKeybeam[4];
	Result* pResult;
	ResultScene* pResultScene;


	ConstValue::Difficulty Diffculty;

	float SpeedValue;
	size_t MappedKeys[4];
	std::vector<Note> Notes[4];
	UINT nextNoteIndex[4];
	size_t noteCount[4];

	struct
	{
		UINT Processed;
		UINT Total;
	}NoteCount;
	

	float Timed;
	float WaitingTime;
	
	bool Waited;

	Rendering::Camera               Camera;
	Rendering::Image::Component		Lane;
	Rendering::Image::Component     Background;

public:
	void Start()  override;
	ConstValue::SceneList Update() override;
	void End()    override;
};