#include "stdafx.h"
#include "Combo.h"

Combo::Combo()
{
	CurrentCombo = 0;
	StrCombo = "";
	TextCombo.Content = StrCombo.data();
	TextCombo.Length = { 200, 50 };
	TextCombo.Location = {340, 280};
	TextCombo.Font = { "CookieRun Bold", 50};
	TextCombo.Color = {255, 255, 255};
}

void Combo::Update(ConstValue::Judge const& judge)
{
	if (judge == ConstValue::Judge::Miss)
	{
		CurrentCombo = 0;
		StrCombo = "0";
		return;
	}
	CurrentCombo++;
	if (MaxCombo < CurrentCombo) MaxCombo = CurrentCombo;
	StrCombo = std::to_string(CurrentCombo);
}

UINT Combo::GetMaxCombo()
{
	return MaxCombo;
}

void Combo::Draw()
{
	TextCombo.Draw();
}
