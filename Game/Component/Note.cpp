#include "stdafx.h"
#include "Note.h"


//판정을 반환
ConstValue::Judge Note::Judge(UINT const& inputTiming)
{
	using namespace ConstValue;
	UINT const diff = Timing < inputTiming ? Timing - inputTiming : inputTiming - Timing;

	if (diff <= JudgeRange) return Perfect;
	else if (diff <= MissRange) return Good;
	else return Miss;
}