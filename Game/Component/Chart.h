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
	//TODO: ���̵� �߰� �ʿ�

	//pair<Ÿ�̹�, ��>
	std::vector<std::pair<UINT, UINT>> NoteData[4];
public:
	Chart();
	Chart(std::string const& file);
	void makeNotes(std::vector<Note>(&Notes)[4]);	
};

