#pragma once
#include "Note.h"
#include "Manager/Resource.h"
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

class Chart final
{
private:
	//TODO: ���̵� �߰� �ʿ�
	bool isChartExist;
	//pair<Ÿ�̹�, ��>
	std::vector<std::pair<UINT, UINT>> NoteData[4];
public:
	Chart();
	Chart(std::string & notedata);
	void makeNotes(std::vector<Note>(&Notes)[4]);	
};

