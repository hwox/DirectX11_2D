#pragma once

#include "Object/GameObject.h"

class CBGMObj :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CBGMObj();
	~CBGMObj();

private:
	class CAudio*	m_pAudio;

	int Stage;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetStageBGM(int stage);
};

