#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"
class CStage3Map :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CStage3Map();
	~CStage3Map();

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
	vector<class CMapObstacle*>			m_MapSlopeList; // �ٵ� ��縦 �߰��Ϸ��� INIT YPOS�� �ٲ�� �ϴµ� 

	class CSceneComponent*		ObstaclePivot;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MakeMapObstacle();
	void SetStageSize(float minx, float maxx, float miny, float maxy);

};

