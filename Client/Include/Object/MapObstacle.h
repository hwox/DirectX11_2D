#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"

class CMapObstacle :
	public CGameObject
{
public:
	CMapObstacle();
	~CMapObstacle();

private:
	class CColliderRect*		ObstacleCollider;
	class CStaticMeshComponent*	m_pMesh;
	class CProjectileMovementComponent*	m_pMovement;

protected:

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	virtual void SetObstaclePosition(Vector3& mPos);
	virtual void SetObstaclePosition(float x, float y,float z);
	virtual void SetObstacleRotation(Vector3& mPos);
	virtual void SetObstacleColliderExtent(Vector3& mPos);
	virtual void SetObstacleColliderExtent(float x, float y);
};

