#include "stdafx.h"
#include "GeneralSetting.h"

inline int GeneralSetting::getSyncValue() { return SyncValue; }

inline void GeneralSetting::setSyncValue(int const& inputSync) { SyncValue = inputSync; }

size_t* GeneralSetting::getKeys() { return MappedKeys; }

inline void GeneralSetting::setKeys(size_t const inputKeys[4])
{
	for (UINT u = 0; u < 4; u++) MappedKeys[u] = inputKeys[u];
}