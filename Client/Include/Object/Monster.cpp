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
	Skill_Type = 0;
	IsCantGo = false;
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
	InitPos = GetWorldPos();
}

void CMonster::Update(float fTime)
{
	CGameObject::Update(fTime);

}

void CMonster::Render(float fTime)
{
	CGameObject::Render(fTime);
}

bool CMonster::Respawn()
{
	if (IsEnable())
		return false;

	SetWorldPos(InitPos);
	Enable(true);
	return true;

}

void CMonster::SetAttackedByStar(bool onoff)
{
	AttackedByStar = onoff;
}

bool CMonster::GetAttackedByStar()
{
	return AttackedByStar;
}

void CMonster::SetEatingEnd(bool onoff)
{
	EatingEnd = onoff;
}

bool CMonster::GetEatingEnd()
{
	return EatingEnd;
}

void CMonster::GoToBlackHole(float fTime)
{
	//MoveTarget
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

void CMonster::SetPlayerInfo(CGameObject * pObj)
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
		return 0;

	Vector3 vRotAxis = vOriginAxis.Cross(vDir);
	//m_vRelative
	if (vRotAxis.z > 0)
	{
		return 1;
	}
	else if (vRotAxis.z < 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void CMonster::SetSkillType(int type)
{
	Skill_Type = type;
}

int CMonster::GetSkillType()
{
	return Skill_Type;
}

bool CMonster::GetIsUIShow()
{
	return IsUIShow;
}

void CMonster::SetIsUIShow(bool enable)
{
	IsUIShow = enable;
}

void CMonster::SetMonsterName(const char * name)
{
	strcpy_s(m_MonsterName, name);
}

void CMonster::AfterCollisionWithPlayer()
{

}

void CMonster::SetIsEating(bool onoff)
{
	IsEating = onoff;
}

bool CMonster::GetIsEating()
{
	return IsEating;
}



void CMonster::OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime)
{
	if (pDest == nullptr)
		return;

	SetMonsterName(m_MonsterName);

}

void CMonster::SetHP(int hp)
{
	m_Hp = hp;
}


