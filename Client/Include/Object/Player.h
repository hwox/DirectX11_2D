#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"


enum Kirby_State
{
	Stand,
	Sord,

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
	bool m_IsMove; // �����̴� ����

	//bool m_pJumpEnable; // press_time MAX ���� �Ǵ� Ű �Է� ���̸� true �ƴϸ� false
	//bool IsAirMouse; // �Ծȿ� ���� �ӱݰ� �ִ��� �ƴ���
	//bool HasMonster; // �� �ȿ� ���� �����ִ��� �ƴ���

	//bool EatAirIng;
	int m_KirbyState;


	//int EatProcess;
	bool JumpIng = false;  // ���� ���߿� ���ִ��� �ƴ���
	//bool FirstJump;

	float press_time;
	float jump_time;
	//float jump_temp; // ���� �󸶳� �ߴ��� �״ϱ� ���� ��


	float m_pMass; // ���� (�Կ� �� ���� ���� ���� �� ���п� ������)
	//float g; // �߷°��ӵ� �� 
	Vector3 pPos;


	int m_pLifeCount;
	float m_pHP;


	//float m_UPkeyCoolTime;


	bool m_pHasMonster;
	bool m_pHasAir;
	bool m_pIsJumping;
	bool m_pNowEating;  // sŰ�� ���Ƶ��̰� �ִ� ����
	bool m_pJumpKeyInputIng; // jump key ������ �ִ� ����
	bool m_pFishingMonster; //  Blackhole����

	float StageMinX;
	float StageMaxX;
	float StageMinY;
	float StageMaxY;


	bool JumpUp;
	bool JumpDown;

	bool JumpAnimationChangeOnce;

	//int Eat_Skill;

private:
	class CStaticMeshComponent*	m_pMesh;
	class CSceneComponent*		m_pRotPivot;
	class CStaticMeshComponent*	m_pChild1Mesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;
	class CColliderRect*		m_pMapBody;  // �ʿ� �浹ü
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



	void DownKey(float fScale, float fTime);
	void ReturnToIdle(float fTime);
	void EnableMove(float fTime);
	void DisableMove(float fTime);


	/////////////////////////////////////////////////////////////

	void SKeyDown(float fTime);
	void SKeyUp(float fTime);

	void AKeyDown(float fTime);
	void AKeyUp(float fTime);

	void UpKeyDown(float fTime);
	void UpKeyDoubleDown(float fTime);

	//void DownKeyDown(float fTime);

	void ToEatAirState(float fTime); // ���� ���� �ִϸ��̼����� ��ȯ
	void SpitAir(float fTime);
	void SplitStar(float fTime);
	void Yup(float fTime);
	void EatAirFail(float fTime);
	void EatMonsterSuccess(int _type);
	void ComputeJump(float fTime);
	void JumpEnd();

	void CamLimit(float fTime);

	void SetStageMinMax(float minx, float maxx, float miny, float maxy);

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
//		// �ö󰡴ٰ� �����;���  
//	//}
//	}
//	else
//	{
//		// ������ �ʿ� ����
//		float tempY = jump_time + (g / m_pMass);
//		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);
//		jump_time -= 0.05f;
//	}

//}