#pragma once
//#include "E:\200425_ver\Engine\Include\Scene\GameMode.h"

#include "Scene/GameMode.h"

class CStage2Mode :
	public CGameMode
{
public:
	CStage2Mode();
	~CStage2Mode();


public:
	virtual bool Init();


private:
	void SpawnMonster();
	void SetCollidrProfile();
};

