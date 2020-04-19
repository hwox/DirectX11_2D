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
	class CColliderSphere2D*	m_pBodySphere;
	class CColliderOBB2D*		m_pBodyOBB2D;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void NearPlayerCheck(Vector3 pPos);
	virtual void SetPlayer(CGameObject *pObj);
	virtual void SetColliderMode(int mode);

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

