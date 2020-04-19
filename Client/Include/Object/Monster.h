#pragma once
#include "Object/GameObject.h"


enum CM_CHOICE
{
	CM_RECT,
	CM_CIRCLE,
	CM_OBB
};

class CMonster :
	public CGameObject
{
public:
	CMonster();
	~CMonster();

protected:
	bool		IsChasePlayer;
	class CGameObject*			m_Player;
	int			Skill_Type;
private:
	int			ColliderMode;
	int			m_Hp;
private:


public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void NearPlayerCheck(Vector3 pPos);
	virtual void SetPlayer(CGameObject *pObj);
	virtual void SetColliderMode(int mode);
	virtual int LookAt2D(Vector3 pPos);
	virtual int GetSkillType();
public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void SetHP(int hp);
};

