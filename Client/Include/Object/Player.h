#pragma once

#include "Object/GameObject.h"

enum Kirby_State
{
	Stand,
	Sord,

};

#define JUMP_AMOUNT 1.5f

class CPlayer :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayer();
	~CPlayer();

private:
	bool m_pJumpEnable; // press_time MAX 도달 또는 키 입력 중이면 true 아니면 false
	bool IsAirMouse; // 입안에 공기 머금고 있는지 아닌지
	bool HasMonster; // 입 안에 몬스터 갖고있는지 아닌지

	bool EatAirIng;
	int m_KirbyState;


	int EatProcess;
	bool JumpIng = false;  // 지금 공중에 떠있는지 아닌지
	bool FirstJump;

	float press_time;
	float jump_time;

	bool IsJump = false;

	float m_pMass; // 무게 (입에 뭐 있을 때랑 없을 때 구분용 무게임)

	float g; // 중력가속도 값 

	Vector3 PrevPos;
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


	CColliderRect*		m_Zone;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:

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
	void EatIng();

	void JumpInput(float fTime);
	void JumpInputEnd(float fTime);
	void JumpUpdate(float fTime);

	void Up(float fTime);

	void SpitAir(float fTime);

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void StruckedByMonster(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void HitAirZone(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

