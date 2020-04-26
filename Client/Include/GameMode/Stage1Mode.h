#pragma once
#include "E:\200425_ver\Engine\Include\Scene\GameMode.h"
class CStage1Mode :
	public CGameMode
{
public:
	CStage1Mode();
	~CStage1Mode();


public:
	virtual bool Init();


private:
	void SpawnMonster();
	void SetCollidrProfile();
	void CreateAnimation2DSequence();
	void Player_Jump_Texture_Create();
	void Monster_Texture_Create();
	void Effect_Texture_Create();
	void Else_Texture_Create();
	bool CreateMaterial();
};

