#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"


enum Kirby_State
{
	Stand,
	Beam,
	Cutter,
	Ice,
};

#define JUMP_AMOUNT 10.0f

class CPlayer :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayer();
	~CPlayer();

private:
	bool m_IsMove; // 움직이는 상태

	int m_KirbyState;
	int m_SaveState; // 밑에 키 누르면 그떄 kirbystate 에 이거 저장

	float press_time;
	float jump_time;

	float m_pMass; // 무게 (입에 뭐 있을 때랑 없을 때 구분용 무게임)
	Vector3 pPos;

	int m_pLifeCount;
	float m_pHP;

	bool m_pHasMonster;
	bool m_pHasAir;
	bool m_pIsJumping;
	bool m_pNowEating;  // s키로 빨아들이고 있는 상태
	bool m_pJumpKeyInputIng; // jump key 누르고 있는 상태
	bool m_pFishingMonster; //  Blackhole상태

	float StageMinX;
	float StageMaxX;
	float StageMinY;
	float StageMaxY;

	bool JumpUp;
	bool JumpDown;

	bool JumpAnimationChangeOnce;
	bool IsPlayAnimation;

private:
	class CStaticMeshComponent*	m_pMesh;
	class CSceneComponent*		m_pRotPivot;
	class CStaticMeshComponent*	m_pChild1Mesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;
	class CColliderRect*		m_pMapBody;  // 맵용 충돌체
	class CPlayerLife*			m_pLifeBar;

	class CMonster*				m_pEatMonster;
	class CStaticMeshComponent*	BackImage;


public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:

	void PlayerKeySetting();
	void SetPlayerAnimation();
	void MoveSide(float fScale, float fTime);
	void RotationZ(float fScale, float fTime);
	void Fire(float fTime);
	void Delete(float fTime);
	void AnimAttackNotify(float fTime);
	void AttackSpeedUp(float fTime);
	void AttackBufEnd();




	void ReturnToIdle(float fTime);
	void ReturnToMonsterIdle(float fTime);
	void EnableMove(float fTime);
	void DisableMove(float fTime);


	/////////////////////////////////////////////////////////////

	void SKeyDown(float fTime);
	void SKeyUp(float fTime);

	void AKeyDown(float fTime);
	void AKeyUp(float fTime);

	void UpKeyDown(float fTime);
	void UpKeyDoubleDown(float fTime);

	void DownKey(float fScale, float fTime);
	//void DownKeyDown(float fTime);
	void DigestMonster(float fScale, float fTime);

	void ToEatAirState(float fTime); // 공기 먹은 애니메이션으로 전환
	void SpitAir(float fTime);
	void Yup(float fTime);
	void EatAirFail(float fTime);
	void EatMonsterSuccess();
	void ComputeJump(float fTime);
	void JumpEnd();
	void ApplySkill(int state);

	void CamLimit(float fTime);

	void SetStageMinMax(float minx, float maxx, float miny, float maxy);


	void WalkStateAnimation(int state);
	void MonsterWalkStateAnimation(int state);
	void IdleStateAnimation(int state);
	void MonsterIdleStateAnimation(int state);
	void IdleDownStateAnimation(int state);
	void JumpDownStateAnimation(int state);
	void MonsterJumpDownStateAnimation(int state);
	void JumpUpStateAnimation(int state);
	void MonsterJumpUpStateAnimation(int state);
	void DamageStateAnimation(int state);
	void JumpIngStateAnimation(int state);

	void EnablePlayAnimation();
	void DisablePlayAnimation();
public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void StruckedByMonster(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void NotOnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

public:
	float Lerp(float value1, float value2, float amount);

};

//if (/*jump_time > 0.f*/ JumpIng)
//{
//	if (!IsAirMouse)
//	{
//		//if (!m_pJumpEnable) {
//		if (jump_time > 0 && jump_time <= JUMP_AMOUNT)
//		{
//			float tempY = jump_time + (g / m_pMass);
//			m_pMovement->SetMoveSpeed(700.f);
//			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

//			jump_time -= 0.1f;
//			jump_temp += 0.1f;


//			m_pAnimation->ChangeAnimation("KirbyJump");

//			//char buff[100];
//			//sprintf_s(buff, " Press 1  : %f \n", jump_time);
//			//OutputDebugStringA(buff);
//		}
//		//}
//		//else {
//		else if (jump_time < 0 && jump_time >((-1)*jump_temp))
//		{
//			float tempY = jump_time + (g / m_pMass);
//			m_pMovement->SetMoveSpeed(700.f);
//			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

//			jump_time -= 0.1f;


//		}
//		else if (jump_time <= ((-1)*jump_temp) || pPos.y <= 130.f)
//		{
//			JumpIng = false;
//			m_pMovement->SetMoveSpeed(500.f);
//			//JumpInputEnd(fTime);
//			pPos.y = 130.f;
//			jump_time = 0.1f;
//			press_time = 0.f;
//			jump_temp = 0.f;
//		}
//		// 올라가다가 내려와야함  
//	//}
//	}
//	else
//	{
//		// 내려올 필요 없음
//		float tempY = jump_time + (g / m_pMass);
//		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);
//		jump_time -= 0.05f;
//	}

//}