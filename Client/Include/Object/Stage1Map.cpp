#include "Stage1Map.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"
#include "Component/ColliderRect.h"

CStage1Map::CStage1Map()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
	FloorCollider = nullptr;
	FloorPivot = nullptr;
}

CStage1Map::~CStage1Map()
{
	//	SAFE_RELEASE(m_pTileMap);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_BackImage);
	SAFE_RELEASE(FloorCollider);
	SAFE_RELEASE(FloorPivot);
}

bool CStage1Map::Init()
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
	MakeFloorCollider();

	m_pMesh->SetRelativePos(0.f, 50.f, 0.f);
	m_pMesh->SetRelativeScale(10000.f, 1200.f, 1.f);

	m_BackImage->SetRelativePos(0.f, 0.f, 0.f);
	m_BackImage->SetRelativeScale(10000.f, 1200.f, 1.f);



	return true;
}

void CStage1Map::Begin()
{
	CGameObject::Begin();
}

void CStage1Map::Update(float fTime)
{
	CGameObject::Update(fTime);
	FloorCollider;
}

void CStage1Map::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStage1Map::MakeFloorCollider()
{
	FloorPivot = CreateComponent<CStaticMeshComponent>("FloorPivot");

	m_pMesh->AddChild(FloorPivot, TR_POS);
	FloorPivot->SetRelativePos(1000.f, 4000.f, 0.f);

	FloorCollider = CreateComponent<CColliderRect>("Stage1FloorCollider");

	FloorPivot->AddChild(FloorCollider, TR_POS);
	FloorCollider->SetExtent(5000.f,500.f);
	FloorCollider->SetPivot(0.0f, 0.f, 0.f);
	FloorCollider->SetCollisionProfile("Map");
}

