#pragma once
#include "ConstValue.h"
class GeneralSetting
{
private:
	int SyncValue = 0;
	size_t MappedKeys[4] = {};

public:
	inline int getSyncValue();
	inline void setSyncValue(int const &inputSync);
	size_t* getKeys();
	inline void setKeys(size_t const inputKeys[4]);
};