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
	// �� �̰� ���ڶ� �̹��� �ٲ� ������ �׳� �ҷ����� �������ϱ�
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

