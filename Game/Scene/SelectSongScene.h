#pragma once
#include "Manager/Scene.h"
#include "Component/Song.h"

class SelectSongScene final : public Scene
{
private:
	int Selection;
	ConstValue::Difficulty Difficulty;

	Song* NowPlaying;
	Result* BestResult;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;

	Rendering::Image::Component		Thumbnail;
	Rendering::Image::Component		VLine;
	Rendering::Image::Component		Rank;

	Rendering::Text::Component		Title;
	Rendering::Text::Component		Artist;
	Rendering::Text::Component		BestScore;

	Rendering::Animation::Component SelectionBox;

	Rendering::Text::Component		Diff;
private:
	void SetSelection(int& Selection);
	void SetDiff(ConstValue::Difficulty const& diff);
public:
	void Start()  override;
	ConstValue::SceneList Update() override;
	void End()    override;
	
};

