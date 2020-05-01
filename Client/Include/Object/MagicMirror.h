#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"

class CMagicMirror :
	public CGameObject
{
public:
	CMagicMirror();
	~CMagicMirror();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;


protected:



public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

};

