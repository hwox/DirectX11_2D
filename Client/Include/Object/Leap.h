#pragma once
#include "Monster.h"
class CLeap :
	public CMonster
{
public:
	CLeap();
	~CLeap();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CAnimation2D*			m_pAnimation;
	class CCharacterMovementComponent*	m_pMovement;
	class CColliderRect*		m_pBody;




	// �׷� �Ѿ��� ���� ������ ������ �ǳ� �� ������
	//class CColliderPixel*		m_pPixelBody;

	// ��� �׷� �Ѿ��� �װɷ� ���� Pixel�� �ٵ� �̰�
	// ������ �� �ڿ� effect�ϰ� �⺻�� heart�� �ϴ°ɷ� 


protected:
	bool IsBackStep;
	int Skill_Type;
	float WingTime;
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void NearPlayerCheck(Vector3 pPos);
	virtual void SetPlayerInfo(CGameObject *pObj);
	virtual void SetColliderMode(int mode);
	virtual void AfterCollisionWithPlayer();
	virtual void AfterCollisionWithAirZone();
	virtual void SetIsEating(bool onoff);
	virtual bool GetIsEating();
	virtual bool Respawn();

	virtual void GoToBlackHole(float fTime);

public:
	virtual void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	virtual void OnBlockOut(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

};

