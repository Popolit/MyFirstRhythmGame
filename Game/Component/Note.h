#pragma once
#include "Manager/GameValue.h"
#include "Manager/ConstValue.h"

class Note
{
private:
	UINT Timing;
	UINT Length = 0;	//단노트인 경우 0
	Rendering::Image::Component NoteImage;
public:
	Note(UINT timing);
	UINT getTiming();
	void MakeNoteImage(UINT const& lineNum);
	void DrawNote();
	ConstValue::Judge Judge(UINT const& inputTiming);
};

