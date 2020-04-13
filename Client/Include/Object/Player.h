#pragma once

#include "Object/GameObject.h"

enum Kirby_State
{
	Stand,
	Sord,

};

class CPlayer :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayer();
	~CPlayer();

private:
	bool m_pJumpEnable;
	bool IsAirMouse; // 입안에 공기 머금고 있는지 아닌지
	bool EatAirIng;
	int m_KirbyState;
	int EatProcess = 0;

	float press_time = 0.f;
	float jump_time = 0.f;


	bool IsJump = false;
	int JumpCount = 0; // 2중점프


private:
	class CStaticMeshComponent*	m_pMesh;
	class CSceneComponent*		m_pRotPivot;
	class CStaticMeshComponent*	m_pChild1Mesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;
	class CColliderSphere2D*	m_pBodySphere;
	class CColliderOBB2D*		m_pBodyOBB2D;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:


	void MoveUpDown(float fScale, float fTime);
	void MoveSide(float fScale, float fTime);
	void RotationZ(float fScale, float fTime);
	void Fire(float fTime);
	void Delete(float fTime);
	void AnimAttackNotify(float fTime);
	void AttackSpeedUp(float fTime);
	void AttackBufEnd();

	void DownKey(float fScale, float fTime);
	void ReturnToIdle(float fTime);
	void SetJumpEnable();

	void EatSomething(float fTime);
	void EatSomethingEnd(float fTime);

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

