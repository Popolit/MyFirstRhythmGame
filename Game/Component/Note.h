#pragma once
#include "Manager/Resource.h"
#include "Manager/ConstValue.h"

class Note
{
private:
	UINT Timing;
	UINT UpTiming = 0;	//단노트인 경우 0
	bool Pressing = false;

	Rendering::Image::Component NoteImage;
public:
	Note(UINT const& timing, UINT const&length = 0);
	UINT getTiming();
	bool isLong();
	void MakeNoteImage(UINT const& lineNum);
	void DrawNote();
	ConstValue::Judge Judge(UINT const& inputTiming);
	ConstValue::Judge PressedJudge(UINT const& inputTiming);
	ConstValue::Judge UpJudge(UINT const& inputTiming);
};

