#pragma once
class Scene abstract
{
public:
	virtual void Start() abstract;
	virtual UINT Update() abstract;
	virtual void End() abstract;
};