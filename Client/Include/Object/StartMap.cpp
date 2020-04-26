#include "StartMap.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"



CStartMap::CStartMap()
{
	m_pMesh = nullptr;
}
CStartMap::~CStartMap()
{
	SAFE_RELEASE(m_pMesh);
}
bool CStartMap::Init()
{
	if (!CGameObject::Init())
		return false;


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");


	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);


	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1Material");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);


	m_pMesh->SetRelativePos(0.f, 300.f, 0.f);
	m_pMesh->SetRelativeScale(10000.f, 1600.f, 1.f);

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
