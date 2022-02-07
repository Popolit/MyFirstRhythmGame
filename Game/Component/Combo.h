#pragma once
#include "Manager/ConstValue.h"
#include <string>

//�޺��� �ٷ�� Ŭ����
class Combo
{
private:
	UINT CurrentCombo;
	UINT MaxCombo;
	std::string StrCombo;

	Rendering::Text::Component TextCombo;
public:
	Combo();
	void Update(ConstValue::Judge const &judge);
	UINT GetMaxCombo();
	void Draw();
};

