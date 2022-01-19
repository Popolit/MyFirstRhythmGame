#pragma once
#include "ModeScenes.h"
#include "Component/Song.h"

class SelectSongScene final : public ModeScenes
{
private:
	std::string StrTitle;
	size_t Selection;
	size_t SongCount;
	float Volume;
	float LoopLength;
	ConstValue::Difficulty Difficulty;
	std::vector<Song*> SongList;

	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectionBox;

	Rendering::Image::Component		Thumbnail;
	Rendering::Text::Component		Title;
	Rendering::Text::Component		Artist;
	Rendering::Text::Component		MaxScore;
	Rendering::Text::Component		Diff;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};

