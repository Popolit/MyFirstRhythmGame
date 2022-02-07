#pragma once
#include "ResultScene.h"
#include "Manager/Scene.h"
#include "Component/Song.h"

class SelectSongScene final : public Scene
{
private:
	int Selection;
	ConstValue::Difficulty Diff;

	Song* NowPlaying;
	Result* BestResult;
	ResultScene* pResultScene;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	struct
	{
		Rendering::Image::Component		Thumbnail;
		Rendering::Image::Component		VLine;
		Rendering::Image::Component		Rank;
	}Image;

	struct
	{
		Rendering::Text::Component		Title;
		Rendering::Text::Component		Artist;
		Rendering::Text::Component		BestScore;
		Rendering::Text::Component		Diff;
	}Text;

	Rendering::Animation::Component SelectionBox;

	
private:
	void SetSelection(int& Selection);
	void SetDiff();
public:
	void Start()  override;
	ConstValue::SceneList Update() override;
	void End()    override;
	
};

