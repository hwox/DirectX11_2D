#include "Stage3Map.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"
#include "Component/ColliderRect.h"
#include "MapObstacle.h"
#include "MagicMirror.h"

CStage3Map::CStage3Map()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
	//FloorCollider = nullptr;
	//FloorPivot = nullptr;
	ObstaclePivot = nullptr;
}

CStage3Map::~CStage3Map()
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

bool CStage3Map::Init()
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


	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2Material");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("StageBackMaterial");

	m_BackImage->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_BackImage);
	m_pMesh->AddChild(ObstaclePivot, TR_POS | TR_ROT);



	m_BackImage->AddChild(m_pMesh, TR_POS);

	m_pMesh->SetRelativePos(0.f, 10.f, 0.f);
	m_pMesh->SetRelativeScale(8700.f, 1080.f, 1.f);

	m_BackImage->SetRelativePos(0.f, 0.f, 0.f);
	m_BackImage->SetRelativeScale(10000.f, 1200.f, 1.f);


	CMagicMirror*  pMirror  = m_pScene->SpawnObject<CMagicMirror>(Vector3(7670.f, 230.f, 0.f));
	pMirror->SetStageMode(1);
	SAFE_RELEASE(pMirror);

	MakeMapObstacle();

	return true;
}

void CStage3Map::Begin()
{
	CGameObject::Begin();
}

void CStage3Map::Update(float fTime)
{
	CGameObject::Update(fTime);
	//FloorCollider;
}

void CStage3Map::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStage3Map::MakeMapObstacle()
{
	CMapObstacle*	Obstacle1 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle1->SetObstaclePosition(1920.f, 290.f, 1.f);
	Obstacle1->SetObstacleColliderExtent(200.f, 110.f);
	Obstacle1->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle1);
	SAFE_RELEASE(Obstacle1);

	CMapObstacle*	Obstacle1_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle1_top->SetObstaclePosition(1920.f, 365.f, 1.f);
	Obstacle1_top->SetObstacleColliderExtent(200.f, 30.f);
	Obstacle1_top->SetObstacleProfileType(2);
	Obstacle1_top->SetYPosition(365.f);
	m_MapObstacleList.push_back(Obstacle1_top);
	SAFE_RELEASE(Obstacle1_top);




	CMapObstacle*	Obstacle2 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle2->SetObstaclePosition(2770.f, 240.f, 1.f);
	Obstacle2->SetObstacleColliderExtent(200.f, 480.f);
	Obstacle2->SetObstacleProfileType(1);
	Obstacle2->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle2);
	SAFE_RELEASE(Obstacle2);

	CMapObstacle*	Obstacle2_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle2_top->SetObstaclePosition(2770.f, 740.f, 1.f);
	Obstacle2_top->SetObstacleColliderExtent(200.f, 30.f);
	Obstacle2_top->SetObstacleProfileType(2);
	Obstacle2_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle2_top->SetYPosition(740.f);
	m_MapObstacleList.push_back(Obstacle2_top);
	SAFE_RELEASE(Obstacle2_top);




	CMapObstacle*	Obstacle3 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle3->SetObstaclePosition(2970.f, 240.f, 1.f);
	Obstacle3->SetObstacleColliderExtent(200.f, 240.f);
	Obstacle3->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle3->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle3);
	SAFE_RELEASE(Obstacle3);


	CMapObstacle*	Obstacle3_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle3_top->SetObstaclePosition(2970.f, 500.f, 1.f);
	Obstacle3_top->SetObstacleColliderExtent(200.f, 30.f);
	Obstacle3_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle3_top->SetObstacleProfileType(2);
	Obstacle3_top->SetYPosition(500.f);
	m_MapObstacleList.push_back(Obstacle3_top);
	SAFE_RELEASE(Obstacle3_top);



	CMapObstacle*	Obstacle4 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle4->SetObstaclePosition(4850.f, 260.f, 1.f);
	Obstacle4->SetObstacleColliderExtent(570.f, 170.f);
	Obstacle4->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle4->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle4);
	SAFE_RELEASE(Obstacle4);


	CMapObstacle*	Obstacle4_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle4_top->SetObstaclePosition(4850.f, 420.f, 1.f);
	Obstacle4_top->SetObstacleColliderExtent(570.f, 30.f);
	Obstacle4_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle4_top->SetObstacleProfileType(2);
	Obstacle4_top->SetYPosition(420.f);
	m_MapObstacleList.push_back(Obstacle4_top);
	SAFE_RELEASE(Obstacle4_top);


	CMapObstacle*	Obstacle5 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle5->SetObstaclePosition(5250.f, 220.f, 1.f);
	Obstacle5->SetObstacleColliderExtent(200.f,300.f);
	Obstacle5->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle5->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle5);
	SAFE_RELEASE(Obstacle5);


	CMapObstacle*	Obstacle5_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle5_top->SetObstaclePosition(5250.f, 540.f, 1.f);
	Obstacle5_top->SetObstacleColliderExtent(200.f, 30.f);
	Obstacle5_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle5_top->SetObstacleProfileType(2);
	Obstacle5_top->SetYPosition(540.f);
	m_MapObstacleList.push_back(Obstacle5_top);
	SAFE_RELEASE(Obstacle5_top);


	CMapObstacle*	DrainObstacle = m_pScene->SpawnObject<CMapObstacle>();

	DrainObstacle->SetObstaclePosition(4800.f, 580.f, 1.f);
	DrainObstacle->SetObstacleColliderExtent(200.f,800.f);
	DrainObstacle->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	DrainObstacle->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(DrainObstacle);
	SAFE_RELEASE(DrainObstacle);





	CMapObstacle*	Obstacle6 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle6->SetObstaclePosition(5450.f, 250.f, 1.f);
	Obstacle6->SetObstacleColliderExtent(200.f, 70.f);
	Obstacle6->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle6->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle6);
	SAFE_RELEASE(Obstacle6);


	CMapObstacle*	Obstacle6_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle6_top->SetObstaclePosition(5450.f, 330.f, 1.f);
	Obstacle6_top->SetObstacleColliderExtent(200.f, 30.f);
	Obstacle6_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle6_top->SetObstacleProfileType(2);
	Obstacle6_top->SetYPosition(330.f);
	m_MapObstacleList.push_back(Obstacle6_top);
	SAFE_RELEASE(Obstacle6_top);


	CMapObstacle*	Obstacle7 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle7->SetObstaclePosition(6750.f, 250.f, 1.f);
	Obstacle7->SetObstacleColliderExtent(200.f, 100.f);
	Obstacle7->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle7->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle7);
	SAFE_RELEASE(Obstacle7);


	CMapObstacle*	Obstacle7_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle7_top->SetObstaclePosition(6750.f, 360.f, 1.f);
	Obstacle7_top->SetObstacleColliderExtent(200.f, 20.f);
	Obstacle7_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle7_top->SetObstacleProfileType(2);
	Obstacle7_top->SetYPosition(360.f);
	m_MapObstacleList.push_back(Obstacle7_top);
	SAFE_RELEASE(Obstacle7_top);




	CMapObstacle*	Obstacle8 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle8->SetObstaclePosition(7700.f, 650.f, 1.f);
	Obstacle8->SetObstacleColliderExtent(800.f, 90.f);
	Obstacle8->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle8->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle8);
	SAFE_RELEASE(Obstacle8);


	CMapObstacle*	Floor = m_pScene->SpawnObject<CMapObstacle>();

	Floor->SetObstaclePosition(4000.f, 100.f, 1.f);
	Floor->SetObstacleColliderPivot(0.5f, 0.5f, 0.f);
	Floor->SetObstacleColliderExtent(9000.f, 300.f);
	Floor->SetObstacleProfileType(2);
	Floor->SetYPosition(230.f);
	m_MapObstacleList.push_back(Floor);
	SAFE_RELEASE(Floor);
}

void CStage3Map::SetStageSize(float minx, float maxx, float miny, float maxy)
{
	StageSizeMinX = minx;
	StageSizeMaxX = maxx;
	StageSizeMinY = miny;
	StageSizeMaxY = maxy;
}


