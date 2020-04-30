#include "Stage1Map.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"
#include "Component/ColliderRect.h"
#include "MapObstacle.h"

CStage1Map::CStage1Map()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
	//FloorCollider = nullptr;
	//FloorPivot = nullptr;
	ObstaclePivot = nullptr;
}

CStage1Map::~CStage1Map()
{
	//	SAFE_RELEASE(m_pTileMap);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_BackImage);
	SAFE_RELEASE(ObstaclePivot);
	//SAFE_RELEASE(FloorCollider);
	//SAFE_RELEASE(FloorPivot);

	SAFE_RELEASE_VECLIST(m_MapObstacleList);
	SAFE_RELEASE_VECLIST(m_ActiveObstacleList);
	SAFE_RELEASE_VECLIST(m_MapSlopeList);
}

bool CStage1Map::Init()
{
	if (!CGameObject::Init())
		return false;


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_BackImage = CreateComponent<CStaticMeshComponent>("Mesh");
	ObstaclePivot = CreateComponent<CSceneComponent>("MapPivot");

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
	m_pMesh->AddChild(ObstaclePivot, TR_POS | TR_ROT);



	m_BackImage->AddChild(m_pMesh, TR_POS);
	//MakeFloorCollider();

	m_pMesh->SetRelativePos(0.f, 10.f, 0.f);
	m_pMesh->SetRelativeScale(8700.f, 1080.f, 1.f);

	m_BackImage->SetRelativePos(0.f, 0.f, 0.f);
	m_BackImage->SetRelativeScale(10000.f, 1200.f, 1.f);


	MakeMapObstacle();

	return true;
}

void CStage1Map::Begin()
{
	CGameObject::Begin();
}

void CStage1Map::Update(float fTime)
{
	CGameObject::Update(fTime);
	//FloorCollider;
}

void CStage1Map::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStage1Map::MakeMapObstacle()
{
	CMapObstacle*	Obstacle1 = m_pScene->SpawnObject<CMapObstacle>();

	// 1850, 230 / 180, 180
	Obstacle1->SetObstaclePosition(1870.f, 330.f, 1.f);
	Obstacle1->SetObstacleColliderExtent(200.f, 200.f);
	Obstacle1->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle1);
	SAFE_RELEASE(Obstacle1);




	CMapObstacle*	Floor = m_pScene->SpawnObject<CMapObstacle>();

	Floor->SetObstaclePosition(4000.f, 100.f, 1.f);
	Floor->SetObstacleColliderPivot(0.5f, 0.5f, 0.f);
	Floor->SetObstacleColliderExtent(9000.f, 300.f);
	Floor->SetObstacleProfileType(2);
	m_MapObstacleList.push_back(Floor);
	SAFE_RELEASE(Floor);
}

void CStage1Map::SetStageSize(float minx, float maxx, float miny, float maxy)
{
	StageSizeMinX = minx;
	StageSizeMaxX = maxx;
	StageSizeMinY = miny;
	StageSizeMaxY = maxy;
}



