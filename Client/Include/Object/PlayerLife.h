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
	// 그 이거 숫자랑 이미지 바뀔 때마다 그냥 불러오자 귀찮으니까
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

