#pragma once
#include "Note.h"
#include "Manager/GameValue.h"
#include "Song.h"
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

class Chart final : protected Song
{
private:
	//TODO: 난이도 추가 필요

	//pair<타이밍, 롱>
	std::vector<std::pair<UINT, UINT>> NoteData[4];
public:
	Chart();
	Chart(std::string const& file);
	void makeNotes(std::vector<Note>(&Notes)[4]);	
};

