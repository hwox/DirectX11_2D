#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
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
	GAMEOBJECT_DEFAULT()

public:
	CMonster();
	~CMonster();

protected:
	bool		IsChasePlayer;
	bool		IsUIShow;
	class CGameObject*			m_Player;

	char		m_MonsterName[256];

	int			Skill_Type;
	Vector3 InitPos;
	bool IsEating; // 먹히고 있는지
	bool EatingEnd; // 다 먹혔음

	bool AttackedByStar; // 별한테 공격당함
	bool IsCantGo;
	bool AttackedBySkill; // 스킬한테 공격당함
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
	virtual void SetPlayerInfo(CGameObject *pObj);
	virtual void SetColliderMode(int mode);
	virtual int LookAt2D(Vector3 pPos);
	virtual void SetSkillType(int type);
	virtual int GetSkillType();
	virtual bool GetIsUIShow();
	virtual void SetIsUIShow(bool enable);
	virtual void SetMonsterName(const char* name);
	virtual void AfterCollisionWithPlayer();
	virtual void SetIsEating(bool onoff);
	virtual bool GetIsEating();
	virtual bool Respawn();

	virtual void SetAttackedByStar(bool onoff);
	virtual bool GetAttackedByStar();
	virtual void SetAttackedBySkill(bool onoff);
	virtual bool GetAttackedBySkill();
	virtual void SetEatingEnd(bool onoff);
	virtual bool GetEatingEnd();
	virtual void GoToBlackHole(float fTime);

public:
	virtual void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void SetHP(int hp);
};


