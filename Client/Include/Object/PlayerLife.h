#pragma once
#include "Object/GameObject.h"

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
	class CPlayer* m_Player;

	int lifeCount;
	int KirbyState;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetLifeCount(int count);
	void SetKirbyState(int state);
};

