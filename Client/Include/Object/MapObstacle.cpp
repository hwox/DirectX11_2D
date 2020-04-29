#include "MapObstacle.h"
#include "EngineGlobals.h"
#include "Component/ColliderRect.h"
#include "Resource/Material.h"
#include "Scene/Scene.h"

CMapObstacle::CMapObstacle()
{
	ObstacleCollider = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;
}

CMapObstacle::~CMapObstacle()
{
	SAFE_RELEASE(ObstacleCollider);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool CMapObstacle::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	ObstacleCollider = CreateComponent<CColliderRect>("MapObstacleBody");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ObstacleMaterial");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);
	SetRoot(m_pMesh);

	m_pMesh->AddChild(ObstacleCollider, TR_POS);

	ObstacleCollider->SetExtent(100.f, 100.f);
	ObstacleCollider->SetCollisionProfile("MapObject");

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("MapObstacleMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);


	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativeScale(100.f, 100.f, 1.f);

	ObstacleCollider->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CMapObstacle::Begin()
{
	CGameObject::Begin();
}

void CMapObstacle::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CMapObstacle::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CMapObstacle::SetObstaclePosition(Vector3 & mPos)
{
	SetWorldPos(mPos);
}

void CMapObstacle::SetObstaclePosition(float x, float y, float z)
{
	SetWorldPos(x, y, z);
}

void CMapObstacle::SetObstacleRotation(Vector3 & mPos)
{
	SetWorldRotation(mPos);
}

void CMapObstacle::SetObstacleColliderExtent(Vector3 & mPos)
{
	ObstacleCollider->SetExtent(mPos.x, mPos.y);
}

void CMapObstacle::SetObstacleColliderExtent(float x, float y)
{
	ObstacleCollider->SetExtent(x, y);
}
