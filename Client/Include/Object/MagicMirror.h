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

	class CInformationSave*			m_pInfo;
	class CPlayer*					m_pPlayer;
	int StageMode;
protected:



public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	virtual void SetStageMode(int Mode);
	virtual int GetStageMode();


public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

