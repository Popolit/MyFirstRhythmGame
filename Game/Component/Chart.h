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
	//TODO: 난이도 추가 필요
	bool isChartExist;
	//pair<타이밍, 롱>
	std::vector<std::pair<UINT, UINT>> NoteData[4];
public:
	Chart();
	Chart(std::string & notedata);
	void makeNotes(std::vector<Note>(&Notes)[4]);	
};

