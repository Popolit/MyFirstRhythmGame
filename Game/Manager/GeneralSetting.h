#pragma once
class GeneralSetting
{
private:
	int SyncValue = 0;
	float Speed = 0.5f;
	size_t MappedKeys[4] = { 0x44, 0x46, 0x4A, 0x4B };
public:
	inline int getSyncValue() { return SyncValue; }

	inline void setSyncValue(int const& inputSync) { SyncValue = inputSync; }

	inline float getSpeed() { return Speed; }

	inline void setSpeed(float const& inputSpeed) { Speed = inputSpeed; }


	inline void getKeys(size_t(&keys)[4])
	{
		for (UINT u = 0; u < 4; u++) keys[u] = MappedKeys[u];
	}

	inline void setKeys(size_t const inputKeys[4])
	{
		for (UINT u = 0; u < 4; u++) MappedKeys[u] = inputKeys[u];
	}
};