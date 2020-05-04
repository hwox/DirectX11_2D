#pragma once
#include "Monster.h"
class CLeap :
	public CMonster
{
public:
	CLeap();
	~CLeap();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CAnimation2D*			m_pAnimation;
	class CCharacterMovementComponent*	m_pMovement;
	class CColliderRect*		m_pBody;




	// 그럼 총알을 따로 별개로 만들어야 되네 아 귀찮다
	//class CColliderPixel*		m_pPixelBody;

	// 얘는 그럼 총알을 그걸로 하자 Pixel로 근데 이게
	// 터지면 그 뒤에 effect하고 기본은 heart로 하는걸로 


protected:
	bool IsBackStep;
	int Skill_Type;
	float WingTime;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void NearPlayerCheck(Vector3 pPos);
	virtual void SetPlayerInfo(CGameObject *pObj);
	virtual void SetColliderMode(int mode);
	virtual void AfterCollisionWithPlayer();
	virtual void AfterCollisionWithAirZone();
	virtual void SetIsEating(bool onoff);
	virtual bool GetIsEating();
	virtual bool Respawn();

	virtual void GoToBlackHole(float fTime);

public:
	virtual void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	virtual void OnBlockOut(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

};

