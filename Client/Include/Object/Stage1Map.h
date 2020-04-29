#pragma once
#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
class CStage1Map :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CStage1Map();
	~CStage1Map();

private:
	//	class CTileMap*	m_pTileMap;
	class CStaticMeshComponent*	m_pMesh;
	CStaticMeshComponent*	m_BackImage;


	//class CColliderRect*		FloorCollider;
	//class CSceneComponent*		FloorPivot;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	void MakeFloorCollider();
};

