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
	float dist = MyPos.Distance(MyPos, pPos);


	if (dist <= 500.0f)
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

int CMonster::LookAt2D(Vector3 pPos)
{
	Vector3 vOriginAxis = Vector3::Axis[AXIS_Y];
	Vector3 m_vWorldPos = GetWorldPos();
	Vector3 vDir = pPos - m_vWorldPos;

	if (vDir.x == 0.f && vDir.y == 0.f && vDir.z == 0.f)
		return 0;

	vDir.Normalize();

	float fDot = vOriginAxis.Dot(vDir);

	if (fDot >= 0.9999f || fDot <= -0.9999f)
		return 0 ;

	Vector3 vRotAxis = vOriginAxis.Cross(vDir);
	//m_vRelative
	if (vRotAxis.z > 0)
	{
		OutputDebugString(TEXT("¿ÞÂÊ"));
		return 1;
	}
	else if (vRotAxis.z < 0)
	{
		OutputDebugString(TEXT("¿À¸¥ÂÊ"));
		return 2;
	}
	else {
		OutputDebugString(TEXT("DEFAULT"));
		return 0;
	}
}

void CMonster::OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime)
{

}

void CMonster::SetHP(int hp)
{
	m_Hp = hp;
}

