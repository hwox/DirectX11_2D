#pragma once

#include "Object/GameObject.h"


class CBullet :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CBullet();
	~CBullet();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CProjectileMovementComponent*	m_pMovement;
	class CColliderRect*		m_pBody;
	class CAnimation2D*			m_pAnimation;

	int b_Type;
	float DisableTime;
public:
	class CColliderRect* GetBody()	const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetDisableTime(float dTime);
	float GetDisableTime();

	void SetRelativeRotationY(float value);


	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

//	virtual void SetBulletType()
};

