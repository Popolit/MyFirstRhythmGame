#pragma once
#include "ModeScenes.h"
#include "Component/Song.h"

class SelectSongScene final : public ModeScenes
{
private:
	std::string StrTitle;
	size_t Selection;
	size_t SongCount;
	ConstValue::Difficulty Difficulty;

	Song* NowPlaying;


	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectionBox;

	
	Rendering::Text::Component		Diff;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
};

