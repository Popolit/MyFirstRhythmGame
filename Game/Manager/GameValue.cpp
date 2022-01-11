#include "stdafx.h"
#include "GameValue.h"

namespace GameValue
{
	namespace
	{
		int SyncValue = int();
		float SpeedValue = float();
		size_t MappedKeys[4] = { 0, };
	}
	void Start()
	{
		SyncValue = 0;
		SpeedValue = 0.5f;
		MappedKeys[0] = 0x44;
		MappedKeys[1] = 0x46;
		MappedKeys[2] = 0x4A;
		MappedKeys[3] = 0x4B;
	}

	namespace Get
	{
		int SyncValue() { return GameValue::SyncValue; }
		float SpeedValue() { return GameValue::SpeedValue; }
		void Keys(size_t (&target)[4]) { for (UINT u = 0; u < 4; u++) target[u] = GameValue::MappedKeys[u]; }
	}
	namespace Set
	{
		void SyncValue(int const& newSync) { GameValue::SyncValue = newSync; }
		void SpeedValue(float const& newSpeed) { GameValue::SpeedValue = newSpeed; };
		void Keys(size_t (&newKeys)[4]) { for (UINT u = 0; u < 4; u++) GameValue::MappedKeys[u] = newKeys[u]; }
	}
};