#include "StartMap.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"



CStartMap::CStartMap()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
}
CStartMap::~CStartMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_BackImage);
}
bool CStartMap::Init()
{
	if (!CGameObject::Init())
		return false;


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_BackImage = CreateComponent<CStaticMeshComponent>("Mesh");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_BackImage->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);


	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1Material");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("StageBackMaterial");

	m_BackImage->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_BackImage);


	m_BackImage->AddChild(m_pMesh, TR_POS);

	m_pMesh->SetRelativePos(0.f, 10.f, 0.f);
	m_pMesh->SetRelativeScale(8000.f, 1050.f, 1.f);

	m_BackImage->SetRelativePos(0.f, 0.f, 0.f);
	m_BackImage->SetRelativeScale(10000.f, 1200.f, 1.f);


	return true;
}

void CStartMap::Begin()
{
	CGameObject::Begin();
}

void CStartMap::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CStartMap::Render(float fTime)
{
	CGameObject::Render(fTime);
}
