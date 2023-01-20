#include "stdafx.h"
#include "Chart.h"

Chart::Chart()
{
	LongCnt = 0;
	isChartExist = false;
}

Chart::Chart(std::string& notedata) : Chart::Chart()
{
	size_t pos = 0;
	//��Ʈ ������ �Ľ�
	while ((pos = notedata.find('\n')) != std::string::npos)
	{
		std::string ndata = notedata.substr(0, pos);
		int line = ndata[0] - '0';

		size_t x = ndata.find_first_of(',') + sizeof(char);
		size_t y = ndata.find_last_of(',');
		if (y == std::string::npos) break;
		int timing = stoi(ndata.substr(x, y - x));
		int length = stoi(ndata.substr(y + sizeof(char)));

		NoteData[line].push_back({ timing, length });
		notedata.erase(0, pos + sizeof(char));
	}
	//����
	for (UINT u = 0; u < 4; u++) std::sort(NoteData[u].begin(), NoteData[u].end());
	isChartExist = true;
}

//��Ʈ ��ü�� ����ִ� �Լ�
void Chart::makeNotes(std::vector<Note>(&Notes)[4])
{
	if (!isChartExist) return;
	LongCnt = 0;
	int SyncValue = Resource::Get::SyncValue();
	for (UINT u = 0; u < 4; u++)
	{
		for (std::pair<UINT, UINT> ndata : NoteData[u])
		{
			Note note = Note(ndata.first + SyncValue, ndata.second ? ndata.second + SyncValue : 0);
			if (note.isLong()) LongCnt++;
			note.MakeNoteImage(u);
			Notes[u].push_back(note);
		}
	}
}

//�� ��Ʈ�� ������ ��ȯ
UINT Chart::GetLongCnt() { return LongCnt; }