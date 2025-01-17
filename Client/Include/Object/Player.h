#pragma once
#include "Object/GameObject.h"
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"


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
	bool m_pIsAttack; // 공격하는 중인지

	float StageMinX;
	float StageMaxX;
	float StageMinY;
	float StageMaxY;

	bool JumpUp;
	bool JumpDown;

	bool JumpAnimationChangeOnce;
	bool IsPlayAnimation;

	bool m_pIsFootOnFloor;
	bool m_pCantGo;

	float dir;
	float m_pBottomY;
private:
	class CStaticMeshComponent*	m_pMesh;
	class CSceneComponent*		m_pRotPivot;
	class CStaticMeshComponent*	m_pChild1Mesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;
	class CColliderRect*		m_pMapBody;  // 맵용 충돌체
	class CPlayerLife*			u_pLifeBar;

	class CMonster*				m_pEatMonster;
	class CStaticMeshComponent*	BackImage;

	class CInformationSave*			m_pInfo;
	//class CEffectSoundObj*		m_pJPSound;
//	class CEffectSoundObj*		m_pPlayerEffect;


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
	void FireEnd(float fTime);
	void Attack(float fTime);

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
	void DigestMonster(float fScale, float fTime);


	void SpitAir(float fTime);
	void EatAirFail(float fTime);
	void EatMonsterSuccess();
	void ComputeJump(float fTime);
	void JumpEnd();

	void ApplySkill(int state);
	void StarAttack(float fTime);

	void CamLimit(float fTime);

	void SetStageMinMax(float minx, float maxx, float miny, float maxy);


	void WalkStateAnimation();
	void MonsterWalkStateAnimation();
	void IdleStateAnimation();
	void MonsterIdleStateAnimation();
	void IdleDownStateAnimation();
	void JumpDownStateAnimation();
	void MonsterJumpDownStateAnimation();
	void JumpUpStateAnimation();
	void MonsterJumpUpStateAnimation();
	void DamageStateAnimation();
	void JumpIngStateAnimation();
	void DigestionStateAnimation();

	void EnablePlayAnimation(float fTime);
	void DisablePlayAnimation(float fTime);

	void AfterBeamAttack(float fTime);
	void AfterCutterAttack(float fTime);

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void BlockedByObstacleBegin(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void BlockedByObstacleEnd(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void StruckedByMonster(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void NotOnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);


	void CreateNotifyList();
public:
	float Lerp(float value1, float value2, float amount);

public:
	void SetPlayerInfo();
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