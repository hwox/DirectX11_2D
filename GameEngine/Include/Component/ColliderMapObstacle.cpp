#include "ColliderMapObstacle.h"
#include "Transform.h"
#include "Collision.h"


CColliderMapObstacle::CColliderMapObstacle()
{
	m_bTickUpdate = true;

	SetTypeID<CColliderMapObstacle>();

	m_vExtent.x = 30.f;
	m_vExtent.y = 30.f;

	m_vSectionMin = Vector3(0.f, 0.f, 0.f);
	m_vSectionMax = Vector3(30.f, 30.f, 0.f);

	m_eColliderType = COLLIDER_OBSTACLE;
}

CColliderMapObstacle::CColliderMapObstacle(const CColliderMapObstacle & com) :
	CColliderBase(com)

{
	m_vExtent = com.m_vExtent;
}

CColliderMapObstacle::~CColliderMapObstacle()
{
}

void CColliderMapObstacle::SetExtent(float x, float y)
{
	m_vExtent.x = x;
	m_vExtent.y = y;
	m_vExtent.z = 0.f;

	SetRelativeScale(m_vExtent.x, m_vExtent.y, 1.f);
}

Vector3 CColliderMapObstacle::GetExtent() const
{
	return m_vExtent;
}

Vector3 CColliderMapObstacle::GetMin() const
{
	return m_vMin;
}

Vector3 CColliderMapObstacle::GetMax() const
{
	return m_vMax;
}

bool CColliderMapObstacle::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("CColliderMapObstacle");

	return true;
}

void CColliderMapObstacle::Begin()
{
	CColliderBase::Begin();

	SetRelativeScale(m_vExtent.x, m_vExtent.y, 1.f);
}

void CColliderMapObstacle::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vMin = m_pTransform->GetWorldPos() - m_pTransform->GetPivot() * m_vExtent;
	m_vMax = m_vMin + m_vExtent;

	m_vSectionMin = m_vMin;
	m_vSectionMax = m_vMax;
}

void CColliderMapObstacle::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderMapObstacle::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderMapObstacle::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		///return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
	case COLLIDER_SPHERE2D:
		break;
	case COLLIDER_OBB2D:
		break;
	case COLLIDER_PIXEL:
		 break;
	case COLLIDER_POINT:
		break;
	case COLLIDER_OBSTACLE:
		break;
	}

	return false;
}

