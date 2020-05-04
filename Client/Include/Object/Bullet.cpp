#include "Bullet.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/ColliderRect.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h" 
#include "Effect.h"
#include "Monster.h"

CBullet::CBullet()
{
	m_pAnimation = nullptr;
	m_pBody = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;

	b_Type = BT_DEFAULT;
}

CBullet::~CBullet()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

CColliderRect * CBullet::GetBody() const
{
	return m_pBody;
}

bool CBullet::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("BulletBody");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	m_pAnimation->AddAnimation2DSequence("StarBullet");
	m_pAnimation->AddAnimation2DSequence("CutterBullet");


	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_pMesh->SetAnimation2D(m_pAnimation);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletAnimMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(100.f, 100.f);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativeScale(100.f, 100.f, 1.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	m_fActiveTime = 3.0f;
	return true;
}

void CBullet::Begin()
{
	CGameObject::Begin();
	m_pBody->AddBlockCallback<CBullet>(this, &CBullet::OnBlock);
}

void CBullet::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * 500.f);
}

void CBullet::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CBullet::SetDisableTime(float dTime)
{
}

float CBullet::GetDisableTime()
{
	return 0.0f;
}
void CBullet::SetRelativeRotationY(float value)
{
	m_pMesh->SetRelativeRotationY(value);

}
void CBullet::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

	// 몬스터는 좀더 뒤에서 터져야 되는데 얘가 그냥 그 앞에서 터져버려서 {} 안에 따로 만들었음ㅠ
	if (pDest->GetName() == "MapObstacleBody")
	{
		CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(GetWorldPos(),
			Vector3(0.f, 0.f, GetRelativeRot().z));
		OutputDebugString(TEXT("Map Obstacle \n"));
		SAFE_RELEASE(pEffect);
	}
	else if (pDest->GetName() == "MonsterBody")
	{
		Vector3 pPos = GetWorldPos();
		pPos.x += 80.f;
		CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(pPos,
			Vector3(0.f, 0.f, GetRelativeRot().z));
		pEffect->Effect_BulletEffect();
		// 몬스터
		CMonster*	pMonster = (CMonster*)(pDest->GetOwner());
		pMonster->SetAttackedByStar(true);
		OutputDebugString(TEXT("Map Obstacle \n"));
		SAFE_RELEASE(pEffect);
		//SAFE_RELEASE(pMonster);
	}

	else
	{

	}



	Kill();
}

