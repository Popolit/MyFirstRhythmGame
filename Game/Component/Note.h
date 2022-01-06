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
		NoteImage.Location = {- 450 + static_cast<int>(lineNum * 100), Timing - 250 };
	}

	inline void DrawNote() { NoteImage.Draw();}

	//판정을 반환
	ConstValue::Judge Judge(UINT const& inputTiming)
	{
		using namespace ConstValue;
		UINT const diff = Timing > inputTiming ? Timing - inputTiming : inputTiming - Timing;

		if (diff <= JudgeRange) return Perfect;
		else if (diff <= MissRange) return Good;
		else if (diff <= recognizeRange) return Miss;
		else return None;
	}
};

