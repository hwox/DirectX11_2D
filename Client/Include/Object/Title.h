#pragma once

#include "Object/GameObject.h"

class CTitle :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CTitle();
	~CTitle();

private:
	class CText*	m_pText;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

