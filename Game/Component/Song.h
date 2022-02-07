#pragma once
#include "Chart.h"
#include "Manager/Result.h"

//곡에 대한 정보를 가진 클래스
class Song
{
private:
	friend class SelectSongScene;
	friend class ResultScene;
	struct 
	{
		std::string Title;
		std::string Artist;
		std::string BestScores[3];
	}STR;

	//UINT Length;
	UINT Highlight;
	Chart* Charts[3];
	Result* BestResults[3];

public:
	Song();
	Song(std::string const& path);
	~Song();
	Chart* GetChart(ConstValue::Difficulty const&diff);
	void ResultUpdate(Result* newResult);
};

