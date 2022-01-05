#pragma once
class Scene abstract
{
public:
	virtual void Start(GeneralSetting *&generalSetting) abstract;
	virtual UINT Update() abstract;
	virtual void End() abstract;
};