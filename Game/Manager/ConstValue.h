#pragma once
namespace ConstValue
{
	//화면 크기
	const Vector<2> ScreenSize = { 1280, 720 };

	//씬 관련
	enum class SceneList { Title, SelectSong, Option, End, Play, Result, };
	SceneList operator++(SceneList& sl);
	SceneList operator--(SceneList& sl);
	bool operator<(SceneList& A, SceneList& B);

	//옵션  관련
	enum class OptionList { Sync, Speed, Keys };
	OptionList operator++(OptionList& ol);
	OptionList operator--(OptionList& ol);
	bool operator<(OptionList& A, OptionList& B);

	const int MaxSync = 10000;
	const int MinSync = -10000;

	const float MaxSpeed = 20.0f;
	const float DefSpeed = 6.0f;
	const float MinSpeed = 0.5f;

	const float DefVolume = 0.8f;

	const size_t DefKeys[4] = { 0x44, 0x46, 0x4A, 0x4B };

	//선곡 씬 관련
	enum class Difficulty { Easy, Normal, Hard };
	const std::string StrDiffi[3] = { "Easy", "Normal", "Hard" };

	Difficulty operator++(Difficulty& d);
	Difficulty operator--(Difficulty& d);
	std::string const& ToString(Difficulty& d);

	//판정 관련
	enum class Judge { Perfect, Good, Miss, None };

	const UINT JudgeRange = 50;	//ms
	const UINT MissRange = 200; //ms
	const UINT recognizeRange = 400; //ms;

	const UINT MaxScore = 1000000;

	//사운드 관련
	const UINT32 LoopLength = 850000;
	const float Sample = 44.1f;	//샘플링
}

namespace Keycode
{
	//키코드
	std::map<size_t, std::string> const KeyMap =
	{
		{VK_LEFT, "←"},
		{VK_RIGHT, "→"},
		{VK_UP, "↑"},
		{VK_DOWN, "↓"},
		{VK_NUMPAD0, "NUMPAD 0"},
		{VK_NUMPAD1, "NUMPAD 1"},
		{VK_NUMPAD2, "NUMPAD 2"},
		{VK_NUMPAD3, "NUMPAD 3"},
		{VK_NUMPAD4, "NUMPAD 4"},
		{VK_NUMPAD5, "NUMPAD 5"},
		{VK_NUMPAD6, "NUMPAD 6"},
		{VK_NUMPAD7, "NUMPAD 7"},
		{VK_NUMPAD8, "NUMPAD 8"},
		{VK_NUMPAD9, "NUMPAD 9"},
		{VK_OEM_PLUS, "+"},
		{VK_OEM_COMMA, ","},
		{VK_OEM_MINUS, "-"},
		{VK_OEM_PERIOD, "."},
		{VK_OEM_1, ";"},
		{VK_OEM_2, "/"},
		{VK_OEM_3, "`"},
		{VK_OEM_4, "["},
		{VK_OEM_5, "\\"},
		{VK_OEM_6, "]"},
		{VK_OEM_7, "\'"},
		{0x30, "0"},
		{0x31, "1"},
		{0x32, "2"},
		{0x33, "3"},
		{0x34, "4"},
		{0x35, "5"},
		{0x36, "6"},
		{0x37, "7"},
		{0x38, "8"},
		{0x39, "9"},
		{0x41, "A"},
		{0x42, "B"},
		{0x43, "C"},
		{0x44, "D"},
		{0x45, "E"},
		{0x46, "F"},
		{0x47, "G"},
		{0x48, "H"},
		{0x49, "I"},
		{0x4A, "J"},
		{0x4B, "K"},
		{0x4C, "L"},
		{0x4D, "M"},
		{0x4E, "N"},
		{0x4F, "O"},
		{0x50, "P"},
		{0x51, "Q"},
		{0x52, "R"},
		{0x53, "S"},
		{0x54, "T"},
		{0x55, "U"},
		{0x56, "V"},
		{0x57, "W"},
		{0x58, "X"},
		{0x59, "Y"},
		{0x5A, "Z"}
	};

	std::string toString(size_t const& code);
}