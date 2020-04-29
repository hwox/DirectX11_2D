#include "Bullet.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/ColliderRect.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h" 

CBullet::CBullet()
{
	m_pAnimation = nullptr;
	m_pBody = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;

	b_Type = BT_DEFAULT;
}

CBullet::~CBullet()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

CColliderRect * CBullet::GetBody() const
{
	return m_pBody;
}

bool CBullet::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("BulletBody");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	m_pAnimation->AddAnimation2DSequence("StarBullet");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_pMesh->SetAnimation2D(m_pAnimation);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletAnimMaterial");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(100.f, 100.f);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativeScale(100.f, 100.f, 1.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CBullet::Begin()
{
	CGameObject::Begin();
}

void CBullet::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * 500.f);
}

void CBullet::Render(float fTime)
{
	CGameObject::Render(fTime);
}


