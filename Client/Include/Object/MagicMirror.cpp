#include "MagicMirror.h"
#include "EngineGlobals.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"

#include "Component/ColliderRect.h"



CMagicMirror::CMagicMirror()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pBody = nullptr;
}

CMagicMirror::~CMagicMirror()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
}

bool CMagicMirror::Init()
{
	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("MirrorBody");

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pAnimation->AddAnimation2DSequence("MagicMirror");
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);
	SetRoot(m_pMesh);

//	m_pMesh->SetRelativePos(7500.f, 400.f, 0.f);
	m_pMesh->SetRelativeScale(150.f, 220.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	m_pBody->SetExtent(150.f, 250.f);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);
	m_pBody->SetCollisionProfile("SceneChange");
	return true;
}

void CMagicMirror::Begin()
{
	CGameObject::Begin();
}

void CMagicMirror::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CMagicMirror::Render(float fTime)
{
	CGameObject::Render(fTime);
}
