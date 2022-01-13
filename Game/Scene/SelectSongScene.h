#pragma once
#include "ModeScenes.h"
#include <map>
class SelectSongScene final : public ModeScenes
{
private:
	ConstValue::SceneList Selection;
	//std::map<> ;


	Rendering::Camera               Camera;
	Rendering::Image::Component     Background;
	Rendering::Animation::Component SelectionBox;

public:
	void Start()  override;
	ConstValue::SceneList UpdateScene() override;
	void End()    override;
	void PlaySong() override;
};

