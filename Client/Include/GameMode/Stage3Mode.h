#pragma once
//#include "E:\200425_ver\Engine\Include\Scene\GameMode.h"

#include "Scene/GameMode.h"


class CStage3Mode :
	public CGameMode
{
public:
	CStage3Mode();
	~CStage3Mode();


public:
	virtual bool Init();

private:
	void SpawnMonster();
	void SetCollidrProfile();
	bool CreateMaterial();

	//void CreateAnimation2DSequence();
	//void Player_Jump_Texture_Create();
	//void Monster_Texture_Create();
	//void Effect_Texture_Create();
	//void Else_Texture_Create();
	//bool CreateMaterial();
};

