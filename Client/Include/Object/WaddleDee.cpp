#include "WaddleDee.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "EngineGlobals.h"
#include "Scheduler.h"
#include "Resource/ResourceManager.h"
#include "Component/ColliderRect.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "..\Object\Monster.h"


#define MW_STAND_SCALE	170.f

CWaddleDee::CWaddleDee()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pBody = nullptr;
	m_pMovement = nullptr;
}

CWaddleDee::~CWaddleDee()
{

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);

}

bool CWaddleDee::Init()
{

	if (!CMonster::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("MonsterBody");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	m_pAnimation->AddAnimation2DSequence("WaddleDeeIdle");
	m_pAnimation->AddAnimation2DSequence("WaddleDeeMove");
	m_pAnimation->AddAnimation2DSequence("WaddleDeeDamage");
	m_pAnimation->AddAnimation2DSequence("WaddleDeeBlackhole");

	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	//m_pBody->SetRect
	m_pBody->SetExtent(MW_STAND_SCALE - 20.f, MW_STAND_SCALE - 20.f);
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

	m_pMesh->SetRelativeScale(MW_STAND_SCALE, MW_STAND_SCALE, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	m_pMovement->SetMoveSpeed(100.f);

	//////////////////////////////////////////////////////////////////

	SetMonsterName("WaddleDee");
	SetHP(100);


	Skill_Type = 1;

	m_pBody->EnableOverlap(true);
	//m_pBody->CollisionMouse(false);
	SetSkillType(Skill_Type);


	return true;
}

void CWaddleDee::Begin()
{
	CMonster::Begin();
}

void CWaddleDee::Update(float fTime)
{
	CMonster::Update(fTime);


	if (m_Player == nullptr)
		m_Player = GetScene()->GetGameMode()->GetPlayer();

	Vector3 pPos = m_Player->GetWorldPos();
	if(!AttackedBySkill && !AttackedByStar)
		NearPlayerCheck(pPos);


	if (AttackedBySkill)
	{
		m_bActive = false;
		return;
	}

	// 기본으로 움직이기 
	if (!IsEating && !AttackedBySkill) {
		if (!IsChasePlayer)
		{
			m_pAnimation->ChangeAnimation("WaddleDeeIdle");
		}
		else
		{
			if (!IsBackStep)
			{
				m_pAnimation->ChangeAnimation("WaddleDeeMove");

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
					m_pMovement->AddMovement(GetWorldAxis(AXIS_X)*-1);
				}
			}
		}
	}
	else
	{
		GoToBlackHole(fTime);
	}

	
}

void CWaddleDee::Render(float fTime)
{
	CMonster::Render(fTime);
}

void CWaddleDee::NearPlayerCheck(Vector3 pPos)
{
	CMonster::NearPlayerCheck(pPos);
}

void CWaddleDee::SetPlayerInfo(CGameObject * pObj)
{
	CMonster::SetPlayerInfo(pObj);
}

void CWaddleDee::SetColliderMode(int mode)
{
	
}

void CWaddleDee::SetSkillType(int type)
{
	CMonster::SetSkillType(type);

}

int CWaddleDee::GetSkillType()
{
	return CMonster::GetSkillType();
}

void CWaddleDee::OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime)
{
	CMonster::OnBlock(pSrc, pDest, fTime);

	if (pDest == nullptr)
		return;

	if (AttackedBySkill)
		return;

	if (pDest->GetCollisionProfile()->strName == "MapObject")
	{
		IsCantGo = true;
		return;
	}

	if (IsEating) {

		if (EatingEnd)
		{
			//m_bActive = false;
			m_pBody->Kill();
			return;
		}
		m_pAnimation->ChangeAnimation("WaddleDeeBlackhole");
	}
	else if (AttackedByStar)
	{
		if (IsEating || EatingEnd)
		{
			return;
		}
		//AfterCollisionWithAirZone();
		m_pBody->Kill();
		Enable(false);
		//m_bActive = false;
	}
	else {

		IsBackStep = true;
		m_pAnimation->ChangeAnimation("WaddleDeeDamage");
		m_pMovement->BackStep(GetWorldAxis(AXIS_X)*-1);
		GET_SINGLE(CScheduler)->AddSchedule<CWaddleDee>("BackEnd", false, 0.5f, this, &CWaddleDee::AfterCollisionWithPlayer);
	}
}

void CWaddleDee::OnBlockOut(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	IsCantGo = false;
}

void CWaddleDee::AfterCollisionWithPlayer()
{
	m_pMovement->BackStepEnd();

	if(!AttackedBySkill)	
		 m_pAnimation->ChangeAnimation("WaddleIdle");

	IsBackStep = false;
}

void CWaddleDee::AfterCollisionWithAirZone()
{
	Enable(false);
	//Kill();
}

void CWaddleDee::SetIsEating(bool onoff)
{
	CMonster::SetIsEating(onoff);
}

bool CWaddleDee::GetIsEating()
{
	return CMonster::GetIsEating();
}

bool CWaddleDee::Respawn()
{
	return CMonster::Respawn();
}

void CWaddleDee::SetAttackedBySkill(bool onoff)
{
	CMonster::SetAttackedBySkill(onoff);
	m_pAnimation->ChangeAnimation("WaddleDeeDamage");
}

void CWaddleDee::GoToBlackHole(float fTime)
{
	CMonster::GoToBlackHole(fTime);

	m_pMovement->AddMovementTarget(GetScene()->GetGameMode()->GetPlayer()->GetWorldPos());

	// speed늘리고 
	m_pMovement->SetMoveSpeed(900.f);

	// 
}

