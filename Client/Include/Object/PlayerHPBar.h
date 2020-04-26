#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"

class CPlayerHpBar :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayerHpBar();
	~CPlayerHpBar();

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

public:
	void SetPercentHPBar(float percent);
};

