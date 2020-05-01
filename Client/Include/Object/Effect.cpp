#include "Effect.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"

CEffect::CEffect()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pMovement = nullptr;
}

CEffect::~CEffect()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMovement);
}

bool CEffect::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pAnimation->AddAnimation2DSequence("StarBulletEffect");
	m_pAnimation->AddAnimation2DSequence("JumpEffect");
	m_pAnimation->AddAnimation2DSequence("SplitAirEffect");



	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_pMesh->SetAnimation2D(m_pAnimation);


	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletAnimMtrl");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);
	SAFE_RELEASE(pMesh);
	SetRoot(m_pMesh);

	//m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
//	m_pMovement->SetUpdateComponent(m_pMesh);


	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativeScale(120.f, 120.f, 1.f);

	return true;
}

void CEffect::Begin()
{
	CGameObject::Begin();
}

void CEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (BE_Move) {
		AddRelativeRotationZ(270.f * fTime);
	}

	if (JE_Move)
	{
		AddRelativePos(-40.f*fTime, -50.f * fTime, 0.f);
	}

	if (SA_Move)
	{
		AddRelativePos(30.f*fTime, 0.f, 0.f);
	}
}

void CEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CEffect::Effect_BulletEffect()
{
	BE_Move = true;
	m_pAnimation->ChangeAnimation("StarBulletEffect");
	m_pAnimation->CreateNotify("StarBulletEffect", "BulletEffectEnd", 4);
	m_pAnimation->AddNotifyFunction<CEffect>("StarBulletEffect", "BulletEffectEnd", this, &CEffect::PlayEnd);
}

void CEffect::Effect_SplitAir()
{
	SA_Move = true;
	m_pMesh->SetRelativeScale(50.f, 50.f, 1.f);
	m_pAnimation->ChangeAnimation("SplitAirEffect");
	m_pAnimation->CreateNotify("SplitAirEffect", "SplitAirEffectEnd", 5);
	m_pAnimation->AddNotifyFunction<CEffect>("SplitAirEffect", "SplitAirEffectEnd", this, &CEffect::PlayEnd);
}

void CEffect::Effect_JumpEffect()
{
	m_pMesh->SetPivot(0.f, 0.f, 0.f);
	JE_Move = true;
	m_pMesh->SetRelativeScale(50.f, 50.f, 1.f);
	m_pAnimation->ChangeAnimation("JumpEffect");
	m_pAnimation->CreateNotify("JumpEffect", "JumpEffectEnd", 3);
	m_pAnimation->AddNotifyFunction<CEffect>("JumpEffect", "JumpEffectEnd", this, &CEffect::PlayEnd);
}

void CEffect::SetEffectRotationY(float value)
{
	m_pMesh->SetRelativeRotationY(value);
}

void CEffect::JumpEffect_RandomRotation()
{
}

void CEffect::PlayEnd(float fTime)
{
	Kill();
	OutputDebugString(TEXT("аж╟е \n"));
}
