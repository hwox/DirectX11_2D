#pragma once
#include "Object/GameObject.h"

class CPlayerHPBar :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayerHPBar();
	~CPlayerHPBar();

private:
	class CUIBar*	m_pBar;
	class CUIImage*	m_pBack;
	float m_fHP;
	float m_fHPMax;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

};

