#pragma once
#include "Monster.h"
class CWaddleDee :
	public CMonster
{
public:
	CWaddleDee();
	~CWaddleDee();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CAnimation2D*			m_pAnimation;
	class CCharacterMovementComponent*	m_pMovement;
	class CColliderRect*		m_pBody;

private:
	bool IsBackStep;
	int Skill_Type;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void NearPlayerCheck(Vector3 pPos);
	virtual void SetPlayerInfo(CGameObject *pObj);
	virtual void SetColliderMode(int mode);
	virtual void SetSkillType(int type);
	virtual int GetSkillType();
	virtual void AfterCollisionWithPlayer();
	virtual void AfterCollisionWithAirZone();
	virtual void SetIsEating(bool onoff);
	virtual bool GetIsEating();
	virtual bool Respawn();

	virtual void GoToBlackHole(float fTime);
public:
	virtual void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

};

