#pragma once
#include "E:\200425_ver\Engine\Include\Component\SceneComponent.h"
class CInformationSave :
	public CSceneComponent
{
public:
	CInformationSave();
	~CInformationSave();

public:
	int p_SkillType;
	int p_HP;
	int p_LifeCount;

private:

public:
	int GetInformationFromTXT(int& st, float& hp, int& lc);
	void SetInformationToTXT();
	void GetPlayerInformation(int st, float hp, int lc);
};

