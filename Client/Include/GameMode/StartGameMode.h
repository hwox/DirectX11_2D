#pragma once

#include "Scene/GameMode.h"


class CStartGameMode :
	public CGameMode
{
public:
	CStartGameMode();
	~CStartGameMode();

public:
	virtual bool Init();

	void CreateAnimation2DSequence();
	bool CreateMaterial();
	void Player_Stand_Texture_Create();
	void Player_Skill_Beam_Texture_Create();
	void Player_Skill_Cutter_Texture_Create();
	void Monster_Texture_Create();
	void Effect_Texture_Create();
	void Else_Texture_Create();

};

