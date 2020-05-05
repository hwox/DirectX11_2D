#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"
class CStartMap :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()
public:
	CStartMap();
	~CStartMap();

private:
	//	class CTileMap*	m_pTileMap;
	class CStaticMeshComponent*	m_pMesh;
	CStaticMeshComponent*	m_BackImage;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

};

