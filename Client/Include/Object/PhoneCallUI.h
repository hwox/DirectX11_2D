#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
class CPhoneCallUI :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPhoneCallUI();
	~CPhoneCallUI();

private:
	class CUIImage*	m_PhoneImage;
	CUIImage*	m_PhoneBattery[4];

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

};

