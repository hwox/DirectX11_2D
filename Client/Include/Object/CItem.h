#pragma once
//#include "E:\200425_ver\Engine\Include\Object\GameObject.h"
#include "Object/GameObject.h"


class CItem :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CItem();
	~CItem();

protected:
	class CStaticMeshComponent*	itemMesh;
	class CColliderRect*		itemBody;

	// ItemBackEffect
	// µÞ ¹è°æ 
	CStaticMeshComponent*	itemBackMesh;;
	class CAnimation2D*			itemBackAnim;

private:
	int ItemKind;
	

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	int GetItemKind();
	void SetItemKind(int _kind);


};

