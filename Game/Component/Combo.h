#pragma once
#include "Manager/ConstValue.h"
#include <string>
class Combo
{
private:
	UINT CurrentCombo;
	std::string StrCombo;

	Rendering::Text::Component TextCombo;
public:
	Combo();
	void Update(ConstValue::Judge const &judge);
	void Draw();
};

