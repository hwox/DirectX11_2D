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

CWaddleDee::CWaddleDee()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pBodyOBB2D = nullptr;
	m_pBodySphere = nullptr;
	m_pBody = nullptr;
	m_pMovement = nullptr;
}

CWaddleDee::~CWaddleDee()
{

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBodyOBB2D);
	SAFE_RELEASE(m_pBodySphere);
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

	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(100.f, 100.f);
	//m_pBody->SetPivot(0.5f, 0.f, 0.f);

	m_pBody->AddBlockCallback<CMonster>(this, &CMonster::OnBlock);
	m_pBody->SetCollisionProfile("Monster");

	////////////////////////////////////////////////////////////////
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);
	//////////////////////////////////////////////////////////////////

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	//////////////////////////////////////////////////////////////////

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("MonsterMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativeScale(120.f, 120.f, 1.f);

	m_pMovement->SetMoveSpeed(100.f);

	//////////////////////////////////////////////////////////////////

	SetName("WaddleDee");
	SetHP(100);

	return true;
}

void CWaddleDee::Begin()
{
	CMonster::Begin();
}

void CWaddleDee::Update(float fTime)
{
	CMonster::Update(fTime);

	Vector3 pPos = GetScene()->GetGameMode()->GetPlayer()->GetWorldPos();
	NearPlayerCheck(pPos);

	if (m_Player == nullptr)
		return;

// 기본으로 움직이기 
	if (!IsChasePlayer)
	{

		m_pAnimation->ChangeAnimation("WaddleDeeIdle");
		//NearPlayerCheck()
	}
	else
	{
		m_pAnimation->ChangeAnimation("WaddleMove");
		if (fScale < 0.f)
			m_pMesh->SetRelativeRotationY(180.f);

		else
			m_pMesh->SetRelativeRotationY(0.f);

		LookAt(pPos);
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

void CWaddleDee::SetPlayer(CGameObject * pObj)
{
	CMonster::SetPlayer(pObj);
}

void CWaddleDee::SetColliderMode(int mode)
{
	CMonster::SetColliderMode(mode);
}

