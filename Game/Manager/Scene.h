#pragma once
#include "ConstValue.h"
#include "Resource.h"

class Scene abstract
{
protected:
	SoundManager* SM;
public:
	virtual void Start() abstract;
	virtual ConstValue::SceneList Update() abstract;
	virtual void End() abstract;
};