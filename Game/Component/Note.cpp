#include "stdafx.h"
#include "Note.h"

Note::Note(UINT timing) :Timing(timing) {};

UINT Note::getTiming() { return Timing; }

void Note::MakeNoteImage(UINT const& lineNum)
{
	if (lineNum == 0 || lineNum == 3) NoteImage.Content = "NoteWhite";
	else NoteImage.Content = "NoteBlue";
	NoteImage.Length = { 100, 20 };
	NoteImage.Location = { -450 + static_cast<int>(lineNum * NoteImage.Length[0]),
						Timing * GameValue::Get::SpeedValue() / 10 - 250 };
}

void Note::DrawNote() { NoteImage.Draw(); }

//판정을 반환
ConstValue::Judge Note::Judge(UINT const& inputTiming)
{
	using namespace ConstValue;
	UINT const diff = Timing > inputTiming ? Timing - inputTiming : inputTiming - Timing;

	if (diff <= JudgeRange) return Judge::Perfect;
	else if (diff <= MissRange) return Judge::Good;
	else if (diff <= recognizeRange) return Judge::Miss;
	else return Judge::None;
}