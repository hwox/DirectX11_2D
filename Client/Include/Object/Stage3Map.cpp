#include "Stage3Map.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"
#include "Component/ColliderRect.h"
#include "MapObstacle.h"
#include "MagicMirror.h"
#include "MapBlock.h"

CStage3Map::CStage3Map()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
	
	ObstaclePivot = nullptr;
	m_RotPivot = nullptr;
}

CStage3Map::~CStage3Map()
{
	//	SAFE_RELEASE(m_pTileMap);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_BackImage);
	SAFE_RELEASE(ObstaclePivot);
	SAFE_RELEASE(m_RotPivot);
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
	m_RotPivot = CreateComponent<CSceneComponent>("MapPivot");

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

	SetRoot(m_RotPivot);
	m_RotPivot->AddChild(m_BackImage, TR_POS | TR_ROT);
	m_pMesh->AddChild(ObstaclePivot, TR_POS | TR_ROT);

	m_RotPivot->AddChild(m_pMesh, TR_POS);


	m_RotPivot->SetRelativePos(0.f, 0.f, 0.f);

	m_pMesh->SetRelativePos(0.f, 10.f, 0.f);
	m_pMesh->SetRelativeScale(9800.f, 1080.f, 1.f);

	m_BackImage->SetRelativePos(-500.f, 0.f, 0.f);
	m_BackImage->SetRelativeScale(5600.f, 1300.f, 1.f);

	CMagicMirror*  pMirror  = m_pScene->SpawnObject<CMagicMirror>(Vector3(8200.f, 230.f, 0.f));
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

	float XPos = GetScene()->GetGameMode()->GetPlayer()->GetWorldPos().x;
	float XRelativePos = XPos / StageSizeMaxX * 0.5f;

	m_BackImage->SetRelativePos(-500.f + StageSizeMaxX * XRelativePos, 0.f, 0.f);
}

void CStage3Map::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CStage3Map::MakeMapObstacle()
{

	CMapObstacle*	Obstacle1_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle1_top->SetObstaclePosition(800.f, 600.f, 1.f);
	Obstacle1_top->SetObstacleColliderExtent(1600.f, 60.f);
	Obstacle1_top->SetObstacleProfileType(2);
	Obstacle1_top->SetYPosition(600.f);
	m_MapObstacleList.push_back(Obstacle1_top);
	SAFE_RELEASE(Obstacle1_top);




	CMapObstacle*	Obstacle2 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle2->SetObstaclePosition(2790.f, 240.f, 1.f);
	Obstacle2->SetObstacleColliderExtent(170.f, 380.f);
	Obstacle2->SetObstacleProfileType(1);
	Obstacle2->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle2);
	SAFE_RELEASE(Obstacle2);

	CMapObstacle*	Obstacle2_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle2_top->SetObstaclePosition(2790.f, 640.f, 1.f);
	Obstacle2_top->SetObstacleColliderExtent(150.f, 30.f);
	Obstacle2_top->SetObstacleProfileType(2);
	Obstacle2_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle2_top->SetYPosition(640.f);
	m_MapObstacleList.push_back(Obstacle2_top);
	SAFE_RELEASE(Obstacle2_top);

	CMapObstacle*	Up_Floor1 = m_pScene->SpawnObject<CMapObstacle>();

	Up_Floor1->SetObstaclePosition(2500.f, 280.f, 1.f);
	Up_Floor1->SetObstacleColliderPivot(0.5f, 0.5f, 0.f);
	Up_Floor1->SetObstacleColliderExtent(340.f, 90.f);
	Up_Floor1->SetObstacleProfileType(2);
	Up_Floor1->SetYPosition(330.f);
	m_MapObstacleList.push_back(Up_Floor1);
	SAFE_RELEASE(Up_Floor1);



	CMapObstacle*	Obstacle3 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle3->SetObstaclePosition(3850.f, 450.f, 1.f);
	Obstacle3->SetObstacleColliderExtent(1400.f, 160.f);
	Obstacle3->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle3->SetObstacleProfileType(1);
	m_MapObstacleList.push_back(Obstacle3);
	SAFE_RELEASE(Obstacle3);


	CMapObstacle*	Obstacle3_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle3_top->SetObstaclePosition(3850.f, 600.f, 1.f);
	Obstacle3_top->SetObstacleColliderExtent(1400.f, 30.f);
	Obstacle3_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle3_top->SetObstacleProfileType(2);
	Obstacle3_top->SetYPosition(570.f);
	m_MapObstacleList.push_back(Obstacle3_top);
	SAFE_RELEASE(Obstacle3_top);


	CMapObstacle*	Obstacle4 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle4->SetObstaclePosition(3200.f, 600.f, 1.f);
	Obstacle4->SetObstacleColliderExtent(140.f, 120.f);
	Obstacle4->SetObstacleProfileType(1);
	Obstacle4->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle4);
	SAFE_RELEASE(Obstacle4);

	CMapObstacle*	Obstacle4_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle4_top->SetObstaclePosition(3200.f, 730.f, 1.f);
	Obstacle4_top->SetObstacleColliderExtent(140.f, 30.f);
	Obstacle4_top->SetObstacleProfileType(2);
	Obstacle4_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle4_top->SetYPosition(730.f);
	m_MapObstacleList.push_back(Obstacle4_top);
	SAFE_RELEASE(Obstacle4_top);

	CMapObstacle*	Obstacle5 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle5->SetObstaclePosition(5350.f, 240.f, 1.f);
	Obstacle5->SetObstacleColliderExtent(100.f, 180.f);
	Obstacle5->SetObstacleProfileType(1);
	Obstacle5->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle5);
	SAFE_RELEASE(Obstacle5);

	CMapObstacle*	Obstacle5_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle5_top->SetObstaclePosition(5350.f, 430.f, 1.f);
	Obstacle5_top->SetObstacleColliderExtent(100.f, 30.f);
	Obstacle5_top->SetObstacleProfileType(2);
	Obstacle5_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle5_top->SetYPosition(420.f);
	m_MapObstacleList.push_back(Obstacle5_top);
	SAFE_RELEASE(Obstacle5_top);


	CMapObstacle*	Up_Floor2 = m_pScene->SpawnObject<CMapObstacle>();

	Up_Floor2->SetObstaclePosition(5850.f, 280.f, 1.f);
	Up_Floor2->SetObstacleColliderPivot(0.5f, 0.5f, 0.f);
	Up_Floor2->SetObstacleColliderExtent(900.f, 90.f);
	Up_Floor2->SetObstacleProfileType(2);
	Up_Floor2->SetYPosition(330.f);
	m_MapObstacleList.push_back(Up_Floor2);
	SAFE_RELEASE(Up_Floor2);

	CMapObstacle*	Obstacle6 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle6->SetObstaclePosition(6500.f, 240.f, 1.f);
	Obstacle6->SetObstacleColliderExtent(400.f, 450.f);
	Obstacle6->SetObstacleProfileType(1);
	Obstacle6->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle6);
	SAFE_RELEASE(Obstacle6);

	CMapObstacle*	Obstacle6_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle6_top->SetObstaclePosition(6500.f, 690.f, 1.f);
	Obstacle6_top->SetObstacleColliderExtent(400.f, 30.f);
	Obstacle6_top->SetObstacleProfileType(2);
	Obstacle6_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle6_top->SetYPosition(670.f);
	m_MapObstacleList.push_back(Obstacle6_top);
	SAFE_RELEASE(Obstacle6_top);


	CMapObstacle*	Obstacle_Up1 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle_Up1->SetObstaclePosition(5910.f, 700.f, 1.f);
	Obstacle_Up1->SetObstacleColliderExtent(380.f, 20.f);
	Obstacle_Up1->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle_Up1->SetObstacleProfileType(2);
	Obstacle_Up1->SetYPosition(680.f);
	m_MapObstacleList.push_back(Obstacle_Up1);
	SAFE_RELEASE(Obstacle_Up1);

	//////////////////////////////////////////


	// 이게 그 별 발판
	CMapObstacle*	Obstacle7 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle7->SetObstaclePosition(6850.f, 460.f, 1.f);
	Obstacle7->SetObstacleColliderExtent(280.f, 40.f);
	Obstacle7->SetObstacleProfileType(1);
	Obstacle7->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle7);
	SAFE_RELEASE(Obstacle7);

	CMapObstacle*	Obstacle7_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle7_top->SetObstaclePosition(6850.f, 520.f, 1.f);
	Obstacle7_top->SetObstacleColliderExtent(280.f, 10.f);
	Obstacle7_top->SetObstacleProfileType(2);
	Obstacle7_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle7_top->SetYPosition(500.f);
	m_MapObstacleList.push_back(Obstacle7_top);
	SAFE_RELEASE(Obstacle7_top);



	// 별 발판 옆에 구름 
	CMapObstacle*	Obstacle8 = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle8->SetObstaclePosition(7350.f, 430.f, 1.f);
	Obstacle8->SetObstacleColliderExtent(630.f, 80.f);
	Obstacle8->SetObstacleProfileType(1);
	Obstacle8->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	m_MapObstacleList.push_back(Obstacle8);
	SAFE_RELEASE(Obstacle8);

	CMapObstacle*	Obstacle8_top = m_pScene->SpawnObject<CMapObstacle>();

	Obstacle8_top->SetObstaclePosition(7350.f, 510.f, 1.f);
	Obstacle8_top->SetObstacleColliderExtent(630.f, 20.f);
	Obstacle8_top->SetObstacleProfileType(2);
	Obstacle8_top->SetObstacleColliderPivot(0.5f, 0.f, 0.f);
	Obstacle8_top->SetYPosition(500.f);
	m_MapObstacleList.push_back(Obstacle8_top);
	SAFE_RELEASE(Obstacle8_top);





	CMapObstacle*	Floor = m_pScene->SpawnObject<CMapObstacle>();

	Floor->SetObstaclePosition(4000.f, 90.f, 1.f);
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



