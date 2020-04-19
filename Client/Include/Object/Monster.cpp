#include "Monster.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Scene/GameMode.h"
#include "Scheduler.h"
#include "Bullet.h"
#include "Component/ColliderRect.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Resource/Material.h"
#include "Resource/ResourceManager.h"

CMonster::CMonster()
{
	m_Player = nullptr;

	IsChasePlayer = false;
	ColliderMode = CM_RECT;
}

CMonster::~CMonster()
{

	SAFE_RELEASE(m_Player);
}

bool CMonster::Init()
{
	if (!CGameObject::Init())
		return false;


	//GET_SINGLE(CScheduler)->AddSchedule<CMinion>("MinionFire", true, 1.f, this, &CMinion::Fire);
	return true;
}

void CMonster::Begin()
{
	CGameObject::Begin();
}

void CMonster::Update(float fTime)
{
	CGameObject::Update(fTime);



}

void CMonster::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CMonster::NearPlayerCheck(Vector3 pPos)
{

	Vector3 MyPos = GetWorldPos(); 
	float dist = 0.f;

	MyPos.Distance(MyPos, pPos);

	if (dist <= 10.0f)
	{
		IsChasePlayer = true;
	}
	else 
	{
		IsChasePlayer = false;
	}

}

void CMonster::SetPlayer(CGameObject * pObj)
{
	if (m_Player)
	{
		SAFE_RELEASE(m_Player);
		m_Player->AddRef();
	}

	m_Player = pObj;
}

void CMonster::SetColliderMode(int mode)
{
	ColliderMode = mode;
}

void CMonster::LookAt2D(Vector3 pPos)
{

}

void CMonster::OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime)
{

}

void CMonster::SetHP(int hp)
{
	m_Hp = hp;
}

