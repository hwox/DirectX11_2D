#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"

#include "Object/GameObject.h"

class CMapBlock :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CMapBlock();
	~CMapBlock();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CColliderRect*		m_pBody;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	virtual void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	//virtual void 
};

