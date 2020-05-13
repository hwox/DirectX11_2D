#include "MapBlock.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/ColliderRect.h"
#include "Effect.h"


CMapBlock::CMapBlock()
{
	m_pMesh = nullptr;

}

CMapBlock::~CMapBlock()
{
	SAFE_RELEASE(m_pMesh);
}


bool CMapBlock::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("MapBlockBody");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);


	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ObstacleBlockMaterial");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);


	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);


	m_pBody->AddBlockCallback<CMapBlock>(this, &CMapBlock::OnBlock);
	m_pBody->SetCollisionProfile("MapBlock");

	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pMesh->SetRelativeScale(100.f,100.f, 1.f);

	return true;
}

void CMapBlock::Begin()
{
	CGameObject::Begin();
}

void CMapBlock::Update(float fTime)
{
	CGameObject::Update(fTime);

}

void CMapBlock::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CMapBlock::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

	// Èì 
	if (pDest->GetName() == "BulletBody")
	{
		CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(GetWorldPos() ,
			Vector3(0.f, 0.f, GetRelativeRot().z));
		pEffect->Effect_MapBlockBomb();
		OutputDebugString(TEXT("Map Block Obstacle \n"));
		SAFE_RELEASE(pEffect);
	}

	Kill();
}
