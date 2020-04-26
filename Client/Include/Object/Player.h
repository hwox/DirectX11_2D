#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"


enum Kirby_State
{
	Stand,
	Sord,

};

#define JUMP_AMOUNT 7.0f

class CPlayer :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CPlayer();
	~CPlayer();

private:
	bool m_IsMove; // �����̴� ����

	bool m_pJumpEnable; // press_time MAX ���� �Ǵ� Ű �Է� ���̸� true �ƴϸ� false
	bool IsAirMouse; // �Ծȿ� ���� �ӱݰ� �ִ��� �ƴ���
	bool HasMonster; // �� �ȿ� ���� �����ִ��� �ƴ���

	bool EatAirIng;
	int m_KirbyState;


	int EatProcess;
	bool JumpIng = false;  // ���� ���߿� ���ִ��� �ƴ���
	bool FirstJump;

	float press_time;
	float jump_time;
	float jump_temp; // ���� �󸶳� �ߴ��� �״ϱ� ���� ��


	float m_pMass; // ���� (�Կ� �� ���� ���� ���� �� ���п� ������)
	float g; // �߷°��ӵ� �� 
	Vector3 pPos;


	int m_pLifeCount;
	float m_pHP;


	float m_UPkeyCoolTime;


	bool m_pHasMonster;
	bool m_pHasAir;
	bool m_pIsJumping;
	bool m_pNowEating;  // sŰ�� ���Ƶ��̰� �ִ� ����
	bool m_pJumpKeyInputIng; // jump key ������ �ִ� ����


	float StageMinX;
	float StageMaxX;
	float StageMinY;
	float StageMaxY;

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

	class CStaticMeshComponent*	BackImage;

	//class CEffectComponent*		m_pEffect;
	CColliderRect*		m_Zone;

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

	void EatIng();

	void AKey(float fTime);
	void AKeyEnd(float fTime);
	void JumpUpdate(float fTime);

	void Up(float fTime);

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
	void EatMonsterSuccess(float fTime);
	void ComputeJump(float fTime);
	void JumpEnd();
	void MakeAirZone(float fTime);

	void CamLimit(float fTime);

	void SetStageMinMax(float minx, float maxx, float miny, float maxy);

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void StruckedByMonster(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void HitAirZone(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void OnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void NotOnTheMap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

public:
	float Lerp(float value1, float value2, float amount);

};

