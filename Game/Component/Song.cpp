#include "stdafx.h"
#include "Song.h"

Song::Song() {}

//���� ���ϵ��� ������ �Ľ�, ��ü�� �����ϴ� ������
Song::Song(std::string const& path)
{
	using namespace std;
	FILE* pFile = nullptr;
	fopen_s(&pFile, path.data(), "r");
	map<string, map<string, string>> data = Parser::Parse(pFile);

	map<string, string> content = data["MetaData"];

	STR.Title = content["Title"];
	STR.Artist = content["Artist"];
	Highlight = stoi(content["Highlight"]);

	content = data["Notes"];
	Charts[0] = new Chart(content["Easy"]);
	Charts[1] = new Chart(content["Normal"]);
	Charts[2] = new Chart(content["Hard"]);

	content = data["BestScore"];
	if (content.empty())
	{
		BestResults[0] = new Result();
		BestResults[1] = new Result();
		BestResults[2] = new Result();
	}
	else
	{
		BestResults[0] = new Result(content["Easy"]);
		BestResults[1] = new Result(content["Normal"]);
		BestResults[2] = new Result(content["Hard"]);
	}
}

Song::~Song()
{
	for (UINT u = 0; u < 3; u++)
	{
		delete Charts[u];
		Charts[u] = nullptr;
		delete BestResults[u];
		BestResults[u] = nullptr;
	}
}

//���̵��� �´� ä���� ��ȯ�ϴ� �Լ�
Chart* Song::GetChart(ConstValue::Difficulty const& diff)
{
	return Charts[static_cast<int>(diff)];
}

//�÷��� ����� �ݿ��ϴ� �Լ�
void Song::ResultUpdate(Result* newResult)
{
	BestResults[static_cast<int>(Resource::Get::Diff())]->Update(STR.Title, newResult);
	return;
}