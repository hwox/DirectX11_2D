#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"


class CEffect :
	public CGameObject
{
public:

	CEffect();
	~CEffect();

protected:
	class CStaticMeshComponent*	m_pMesh;
	class CAnimation2D*			m_pAnimation;
	class CProjectileMovementComponent*	m_pMovement;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	bool BE_Move;
	bool JE_Move;
	bool SA_Move;

	void Effect_BulletEffect();
	void Effect_SplitAir();
	void Effect_JumpEffect();

	void SetEffectRotationY(float value);

	void JumpEffect_RandomRotation();

	void PlayEnd(float fTime);

	void CreateNotifyLift();
};

