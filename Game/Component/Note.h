#pragma once
#include "Manager/ConstValue.h"

class Note
{
private:
	UINT Timing;
	UINT Length = 0;	//단노트인 경우 0
	Rendering::Image::Component NoteImage;
public:
	Note(UINT timing) :Timing(timing){};

	inline UINT getTiming() { return Timing; }

	inline void MakeNoteImage(UINT const& lineNum)
	{
		NoteImage.Content = "Note";
		NoteImage.Length = { 100, 10 };
		NoteImage.Location = {- 450 + static_cast<int>(lineNum * NoteImage.Length[0]), Timing * 0.5f - 248 };
	}

	inline void DrawNote() { NoteImage.Draw();}

	//판정을 반환
	ConstValue::Judge Judge(UINT const& inputTiming)
	{
		using namespace ConstValue;
		UINT const diff = Timing > inputTiming ? Timing - inputTiming : inputTiming - Timing;

		if (diff <= JudgeRange) return Judge::Perfect;
		else if (diff <= MissRange) return Judge::Good;
		else if (diff <= recognizeRange) return Judge::Miss;
		else return Judge::None;
	}
};

