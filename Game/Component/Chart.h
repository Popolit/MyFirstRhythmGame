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
	bool isChartExist;
	UINT LongCnt;
	std::vector<std::pair<UINT, UINT>> NoteData[4];	//pair<타이밍, 롱노트>
public:
	Chart();
	Chart(std::string & notedata);
	void makeNotes(std::vector<Note>(&Notes)[4]);	
	UINT GetLongCnt();
};

