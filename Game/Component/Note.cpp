#include "stdafx.h"
#include "Note.h"

Note::Note(UINT const& timing, UINT const& uptiming) :Timing (timing), UpTiming (uptiming) {};

UINT Note::getTiming() { return Timing; }

bool Note::isLong()
{
	return 0 < UpTiming;
}

void Note::MakeNoteImage(UINT const& lineNum)
{
	if (lineNum == 0 || lineNum == 3) NoteImage.Content = "NoteWhite";
	else NoteImage.Content = "NoteBlue";

	Vector<2> location;
	float height = 20.0f;

	location[0] = - 450.0f + static_cast<float>(lineNum * 100);
	//롱노트일 경우
	if (UpTiming)
	{
		height += (UpTiming - Timing) * Resource::Get::SpeedValue() / 10;
		location[1] = (Timing + UpTiming) * Resource::Get::SpeedValue() / 20 - 243;
	}
	else location[1] = Timing * Resource::Get::SpeedValue() / 10 - 243;

	NoteImage.Length = { 100, height };
	NoteImage.Location = location;
}

void Note::DrawNote() { NoteImage.Draw(); }

//판정을 반환
ConstValue::Judge Note::Judge(UINT const& inputTiming)
{
	using namespace ConstValue;
	
	UINT const diff = Timing > inputTiming ? Timing - inputTiming : inputTiming - Timing;

	if (diff <= JudgeRange)
	{
		Pressing = true;
		return Judge::Perfect;
	}
	else if (diff <= MissRange)
	{
		Pressing = true;
		return Judge::Good;
	}
	else if (diff <= recognizeRange) return Judge::Miss;
	else return Judge::None;
}

//롱노트 누르고 있을 때 판정
ConstValue::Judge Note::PressedJudge(UINT const& inputTiming)
{
	using namespace ConstValue;
	if (!Pressing) return Judge::None;

	if (UpTiming >= inputTiming)
	{
		NoteImage.Length[1] = 20 + (UpTiming - inputTiming) * Resource::Get::SpeedValue() / 10;
		NoteImage.Location[1] = (inputTiming + UpTiming) * Resource::Get::SpeedValue() / 20 - 243;
	}
	else NoteImage.Length[1] = 0;

	if (inputTiming < UpTiming) return Judge::Perfect;
	if (inputTiming - UpTiming > recognizeRange) return Judge::Miss;
	else return Judge::None;
}

//롱노트 뗄 때 판정
ConstValue::Judge Note::UpJudge(UINT const& inputTiming)
{
	using namespace ConstValue;
	if (!Pressing) return Judge::None;
	UINT const diff = UpTiming > inputTiming ? UpTiming - inputTiming : inputTiming - UpTiming;

	if (diff <= JudgeRange) return Judge::Perfect;
	else if (diff <= MissRange) return Judge::Good;
	else return Judge::Miss;
}