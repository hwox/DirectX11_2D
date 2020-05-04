#include "Leap.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "EngineGlobals.h"
#include "Scheduler.h"
#include "Resource/ResourceManager.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"



#define LP_STAND_SCALE	130.f

CLeap::CLeap()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pMovement = nullptr;
	m_pBody = nullptr;


	WingTime = 0.f;
}

CLeap::~CLeap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);
}

bool CLeap::Init()
{
	if (!CMonster::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("MonsterBody");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pAnimation->AddAnimation2DSequence("LeapIdle");

	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(LP_STAND_SCALE - 20.f, LP_STAND_SCALE - 20.f);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);


	m_pBody->AddBlockCallback<CMonster>(this, &CMonster::OnBlock);
	m_pBody->SetCollisionProfile("Monster");

	////////////////////////////////////////////////////////////////
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);
	//////////////////////////////////////////////////////////////////



	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MonsterAnimMtrl");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	//////////////////////////////////////////////////////////////////

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("MonsterMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativeScale(LP_STAND_SCALE, LP_STAND_SCALE, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	m_pMovement->SetMoveSpeed(100.f);

	//////////////////////////////////////////////////////////////////

	SetMonsterName("Leap");
	SetHP(100);


	Skill_Type = 2;

	SetSkillType(Skill_Type);
	m_pBody->EnableOverlap(true);
	
	return true;
}

void CLeap::Begin()
{
	CMonster::Begin();
}

void CLeap::Update(float fTime)
{
	CMonster::Update(fTime);



	if (m_Player == nullptr)
		m_Player = GetScene()->GetGameMode()->GetPlayer();

	Vector3 pPos = m_Player->GetWorldPos();
	NearPlayerCheck(pPos);

	WingTime += fTime;



	if (!IsEating) {
		if (!IsChasePlayer)
		{
			m_pAnimation->ChangeAnimation("LeapIdle");
			if ((int)WingTime % 2 == 0)
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * 0.5f);
			}
			else
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * -0.5f);
			}
		}
		else
		{
			if (!IsBackStep)
			{
				m_pAnimation->ChangeAnimation("LeapIdle");

				int turn = LookAt2D(pPos);
				switch (turn)
				{
				case 1:
					//왼쪽
					m_pMesh->SetRelativeRotationY(0.f);
					break;
				case 2:
					// 오른쪽
					m_pMesh->SetRelativeRotationY(180.f);
					break;
				}

				if (!IsCantGo) {
				//	m_pMovement->AddMovement(GetWorldAxis(AXIS_X)*-1);
				}
			}
		}
	}
	else
	{
		GoToBlackHole(fTime);
	}
}

void CLeap::Render(float fTime)
{
	CMonster::Render(fTime);
}

void CLeap::NearPlayerCheck(Vector3 pPos)
{
	CMonster::NearPlayerCheck(pPos);
}

void CLeap::SetPlayerInfo(CGameObject * pObj)
{
	CMonster::SetPlayerInfo(pObj);
}

void CLeap::SetColliderMode(int mode)
{
	CMonster::SetColliderMode(mode);
}

void CLeap::AfterCollisionWithPlayer()
{
	m_pMovement->BackStepEnd();
	m_pAnimation->ChangeAnimation("LeapIdle");
	IsBackStep = false;
}

void CLeap::AfterCollisionWithAirZone()
{
	Enable(false);
}

void CLeap::SetIsEating(bool onoff)
{
	CMonster::SetIsEating(onoff);
}

bool CLeap::GetIsEating()
{
	return CMonster::GetIsEating();
}

bool CLeap::Respawn()
{
	return CMonster::Respawn();
}

void CLeap::GoToBlackHole(float fTime)
{

	CMonster::GoToBlackHole(fTime);

	m_pMovement->AddMovementTarget(GetScene()->GetGameMode()->GetPlayer()->GetWorldPos());

	// speed늘리고 
	m_pMovement->SetMoveSpeed(900.f);
}

void CLeap::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

	if (pDest == nullptr)
		return;

	if (pDest->GetCollisionProfile()->strName == "MapObject")
	{
		IsCantGo = true;
		return;
	}

	if (IsEating) {

		if (EatingEnd)
		{
			m_pBody->Kill();
			return;
		}
		m_pAnimation->ChangeAnimation("LeapDamage");
	}
	else if (AttackedByStar)
	{
		if (IsEating || EatingEnd)
		{
			OutputDebugString(TEXT("있어서는 안될 상황 ^ㅁ^;; \n"));
			return;
		}

		AfterCollisionWithAirZone();
		m_pBody->Kill();
	}
	else {

		IsBackStep = true;
		m_pAnimation->ChangeAnimation("LeapDamage");
		m_pMovement->BackStep(GetWorldAxis(AXIS_X)*-1);
		GET_SINGLE(CScheduler)->AddSchedule<CLeap>("BackEnd", false, 0.5f, this, &CLeap::AfterCollisionWithPlayer);
	}
}

void CLeap::OnBlockOut(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr)
		return;

	IsCantGo = false;
}
