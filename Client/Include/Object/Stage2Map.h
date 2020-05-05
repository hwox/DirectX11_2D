#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"

#include "Object/GameObject.h"
class CStage2Map :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CStage2Map();
	~CStage2Map();

	float StageSizeMinX;
	float StageSizeMaxX;
	float StageSizeMinY;
	float StageSizeMaxY;

private:
	//	class CTileMap*	m_pTileMap;
	class CStaticMeshComponent*	m_pMesh;
	CStaticMeshComponent*	m_BackImage;


	vector<class CMapObstacle*>			m_MapObstacleList;
	vector<class CMapObstacle*>			m_ActiveObstacleList;

	class CSceneComponent*		ObstaclePivot;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MakeMapObstacle();
	void SetStageSize(float minx, float maxx, float miny, float maxy);

};

