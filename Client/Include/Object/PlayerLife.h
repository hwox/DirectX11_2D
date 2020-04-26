#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "..\Object\PlayerHPBar.h"

//enum Kirby_State
//{
//	KS_STANDARD,
//	KS_SORD,
//	KS_END
//};


#define LIFEMAX 5
class CPlayerLife :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayerLife();
	~CPlayerLife();

private:
	// 그 이거 숫자랑 이미지 바뀔 때마다 그냥 불러오자 귀찮으니까
	class CUIImage*	m_Image;
	CUIImage*	m_NumberCount;
	CUIImage*	m_NumberCount_zero;
	CUIImage*	m_ImageX;

	class CPlayerHpBar*	m_pHPBar;

	int lifeCount;
	int KirbyState;

	float m_pHP;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


public:

	void SetLifeCount(int count);
	void SetKirbyState(int state);
	void SetHP(float hp);
	float GetHP();

};

