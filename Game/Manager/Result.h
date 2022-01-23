#pragma once

class Result
{
private:
	UINT Score;
	UINT MaxCombo;
	struct 
	{
		UINT Perfect;
		UINT Good;
		UINT Miss;
	}Count;
public:
	Result();

};