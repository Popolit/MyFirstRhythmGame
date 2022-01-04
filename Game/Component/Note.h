#pragma once
#include "Manager/ConstValue.h"

class Note
{
private:
	UINT Timing;
public:
	Note(UINT timing) :Timing(timing){};
	ConstValue::Judge Judge(UINT const& inputTiming);
};

