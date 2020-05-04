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

	float m_pY;
protected:

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	virtual void SetObstaclePosition(Vector3& mPos);
	virtual void SetObstaclePosition(float x, float y,float z);
	virtual void SetObstacleColliderExtent(Vector3& mPos);
	virtual void SetObstacleColliderExtent(float x, float y);
	virtual void SetObstacleColliderPivot(float x, float y, float z);
	virtual void SetObstacleProfileType(int type);

	virtual float GetYPosition();
	virtual void SetYPosition(float y);
public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

