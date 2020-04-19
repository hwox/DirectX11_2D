#pragma once

#include "Scene/GameMode.h"

class CMainGameMode :
	public CGameMode
{
public:
	CMainGameMode();
	~CMainGameMode();

public:
	virtual bool Init();

private:
	bool CreateMaterial();
	bool CreateAnimation2DSequence();
	void Player_Jump_Texture_Create();
	void Monster_Texture_Create();
};

