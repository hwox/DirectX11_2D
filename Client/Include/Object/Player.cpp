#include "Player.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Bullet.h"
#include "Component/ProjectileMovementComponent.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Scheduler.h"
#include "Component/ColliderRect.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "EffectSoundObj.h"


CPlayer::CPlayer()
{
	m_pBodyOBB2D = nullptr;
	m_pBodySphere = nullptr;
	m_pBody = nullptr;
	m_pAnimation = nullptr;
	m_pCamera = nullptr;
	m_pRotPivot = nullptr;
	m_pChild1Mesh = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;


	IsAirMouse = false;
	m_KirbyState = 0;
	m_pJumpEnable = true;
}

CPlayer::~CPlayer()
{
	SAFE_RELEASE(m_pBodyOBB2D);
	SAFE_RELEASE(m_pBodySphere);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pChild1Mesh);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool CPlayer::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");
	m_pChild1Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pCamera = CreateComponent<CCameraComponent>("Camera");
	m_pBody = CreateComponent<CColliderRect>("PlayerBody");
	//m_pBodySphere = CreateComponent<CColliderSphere2D>("PlayerBodySphere");
	//m_pBodyOBB2D = CreateComponent<CColliderOBB2D>("PlayerBodyOBB2D");

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	m_pAnimation->AddAnimation2DSequence("KirbyIdle");
	m_pAnimation->AddAnimation2DSequence("KirbyWalk");
	m_pAnimation->AddAnimation2DSequence("KirbyIdleDown");
	m_pAnimation->AddAnimation2DSequence("KirbyDown");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpEnd");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpIng");
	m_pAnimation->AddAnimation2DSequence("KirbyJump");
	m_pAnimation->AddAnimation2DSequence("KirbyEat");
	m_pAnimation->AddAnimation2DSequence("KirbyEatOver");


	m_pMesh->SetAnimation2D(m_pAnimation);

	m_pMesh->AddChild(m_pBody, TR_POS);
	//m_pMesh->AddChild(m_pBodySphere, TR_POS);
	//m_pMesh->AddChild(m_pBodyOBB2D, TR_ROT | TR_POS);

	m_pBody->SetExtent(200.f, 200.f);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);

	m_pBody->AddBlockCallback<CPlayer>(this, &CPlayer::OnBlock);
	m_pBody->SetCollisionProfile("Player");

	/*m_pBodySphere->SetSphere(Vector3(200.f, 0.f, 0.f), 100.f);

	m_pBodySphere->AddBlockCallback<CTestObject>(this, &CTestObject::OnBlock);
	m_pBodySphere->SetCollisionProfile("Player");

	m_pBodyOBB2D->SetOBB2D(Vector3(0.f, 0.f, 0.f), 100.f, 100.f);

	m_pBodyOBB2D->AddBlockCallback<CTestObject>(this, &CTestObject::OnBlock);
	m_pBodyOBB2D->SetCollisionProfile("Player");*/

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_pChild1Mesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	m_pChild1Mesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pCamera, TR_POS);

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f, -20.f);

	m_pChild1Mesh->SetRelativePos(-200, 0.f, 0.f);
	m_pChild1Mesh->SetRelativeScale(100.f, 100.f, 1.f);


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);

	m_pRotPivot->AddChild(m_pChild1Mesh, TR_POS | TR_ROT);

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativePos(500.f, 500.f, 0.f);
	m_pMesh->SetRelativeScale(200.f, 200.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	/*GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_W, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_S, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("MoveUpDown", this, &CPlayer::MoveUpDown);*/

	GET_SINGLE(CInput)->AddAxisKey("RotationZ", DIK_D, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("RotationZ", DIK_A, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("RotationZ", this, &CPlayer::MoveSide);

	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_SPACE);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Fire", AKS_PRESS, this, &CPlayer::Fire);


	GET_SINGLE(CInput)->AddAxisKey("IdleKeyDown", DIK_DOWN, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("IdleKeyDown", this, &CPlayer::DownKey);

	GET_SINGLE(CInput)->AddActionKey("Blackhole", DIK_S);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Blackhole", AKS_PRESS, this, &CPlayer::EatSomething);

	GET_SINGLE(CInput)->AddActionKey("BlackholeEnd", DIK_S);
	GET_SINGLE(CInput)->BindAction<CPlayer>("BlackholeEnd", AKS_RELEASE, this, &CPlayer::EatSomethingEnd);

	GET_SINGLE(CInput)->AddActionKey("DeleteChild", DIK_RETURN);
	GET_SINGLE(CInput)->BindAction<CPlayer>("DeleteChild", AKS_PRESS, this, &CPlayer::Delete);

	GET_SINGLE(CInput)->AddActionKey("AttackSpeedUp", DIK_1);
	GET_SINGLE(CInput)->BindAction<CPlayer>("AttackSpeedUp", AKS_PRESS, this, &CPlayer::AttackSpeedUp);


	return true;
}

void CPlayer::Begin()
{
	CGameObject::Begin();
}

void CPlayer::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pRotPivot->AddRelativeRotationZ(180.f * fTime);

	OutLineCBuffer	tBuffer = {};
	tBuffer.iPixelSize = 5;

	Animation2DFrameInfo	tFrameInfo = m_pAnimation->GetAnimFrame();

	tBuffer.vScale = Vector2(m_pMesh->GetWorldScale().x, m_pMesh->GetWorldScale().y);
	tBuffer.vImageSize = tFrameInfo.vEnd - tFrameInfo.vStart;

	m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);

	if (GET_SINGLE(CInput)->RButtonDown())
	{
		Vector2 vMousePos = GET_SINGLE(CInput)->GetMouseWorldPos();

		Vector3 vTarget = Vector3(vMousePos.x, vMousePos.y, 0.f);
		m_pMovement->MoveNav(vTarget);
	}

	//if (m_pMovement->GetVelocity() == 0.f)
	//	m_pAnimation->ChangeAnimation("MinionIdle");
}

void CPlayer::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CPlayer::MoveUpDown(float fScale, float fTime)
{
	/*char	strText[256] = {};
	sprintf_s(strText, "Scale : %.f\n", fScale);

	OutputDebugStringA(strText);*/

	static bool	bMove = false;

	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * fScale);

	if (fScale != 0.f)
	{
		bMove = true;
		m_pAnimation->ChangeAnimation("KirbyWalk");
	}

	else
	{
		if (bMove)
		{
			m_pAnimation->ChangeAnimation("KirbyIdle");
			bMove = false;
		}
	}
}

void CPlayer::MoveSide(float fScale, float fTime)
{
	static bool	bMove = false;

	if (fScale != 0.f)
	{
		bMove = true;
		m_pAnimation->ChangeAnimation("KirbyWalk");

		if (fScale < 0.f)
			m_pMesh->SetRelativeRotationY(180.f);

		else
			m_pMesh->SetRelativeRotationY(0.f);

		m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
	}

	else
	{
		if (bMove)
		{
			m_pAnimation->ChangeAnimation("KirbyIdle");
			bMove = false;
		}
	}
}

void CPlayer::RotationZ(float fScale, float fTime)
{
	m_pMovement->AddRotationZ(180.f * fScale);
}

void CPlayer::Fire(float fTime)
{
	//m_pAnimation->ChangeAnimation("MinionKick");

	CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	pMovement->SetDistance(500.f);

	SAFE_RELEASE(pMovement);

	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(pBullet);

	CEffectSoundObj*	pFireSound = m_pScene->SpawnObject<CEffectSoundObj>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	pFireSound->SetSound("Demasia", "Demasia.mp3");

	SAFE_RELEASE(pFireSound);
}

void CPlayer::Delete(float fTime)
{
	/*CGameObject*	pChild = m_vecChild[0];

	if (pChild)
		DeleteChild(pChild);*/

	DeleteChild("Child");
}

void CPlayer::AnimAttackNotify(float fTime)
{
	/*CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		GetRelativeRot());

	CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	pMovement->SetDistance(500.f);

	SAFE_RELEASE(pMovement);

	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(pBullet);*/
}

void CPlayer::AttackSpeedUp(float fTime)
{
	CAnimation2DSequence* pSequence = m_pAnimation->FindAnimSequence("MinionKick");

	if (pSequence)
	{
		pSequence->SetPlayScale(1.5f);
		SAFE_RELEASE(pSequence);

		GET_SINGLE(CScheduler)->AddSchedule<CPlayer>("AttackSpeedUp", false, 5.f, this, &CPlayer::AttackBufEnd);
	}
}

void CPlayer::AttackBufEnd()
{
	CAnimation2DSequence* pSequence = m_pAnimation->FindAnimSequence("MinionKick");

	if (pSequence)
	{
		pSequence->SetPlayScale(1.f);
		SAFE_RELEASE(pSequence);
	}
}

void CPlayer::DownKey(float fScale, float fTime)
{
	static bool	bMove = false;

	if (fScale != 0.f)
	{
		bMove = true;
		m_pAnimation->ChangeAnimation("KirbyIdleDown");
	}
	else
	{
		if (bMove)
		{
			m_pAnimation->ChangeAnimation("KirbyIdle");
			bMove = false;
		}
	}
}

void CPlayer::ReturnToIdle(float fTime)
{
	m_pAnimation->ChangeAnimation("KirbyIdle");
}

void CPlayer::SetJumpEnable()
{
	m_pJumpEnable = true;
}

void CPlayer::EatSomething(float fTime)
{

	switch (EatProcess)
	{
	case 0:
		// Ã³À½ ¸Ô´ÂÁß
		EatAirIng = true;

		m_pAnimation->ChangeAnimation("KirbyEat");
		m_pAnimation->CreateNotify("KirbyEat", "EatOver", 14);
		m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEat", "EatOver", this, &CPlayer::EatSomethingEnd);
		EatProcess = 1;
		OutputDebugString(TEXT("11111111\n"));
		break;
	case 1:
		// ¸Ô´ÂÁß 
		OutputDebugString(TEXT("3333333\n"));
		break;
	case 2:
		if (EatAirIng)
		{

			EatAirIng = false;
			m_pAnimation->ChangeAnimation("KirbyEatOver");
			m_pAnimation->CreateNotify("KirbyEatOver", "ReturnToIdle", 3);
			m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "ReturnToIdle", this, &CPlayer::ReturnToIdle);
			EatProcess = 0;
			OutputDebugString(TEXT("3333333\n"));
		}
		break;
	}

}

void CPlayer::EatSomethingEnd(float fTime)
{
	EatProcess = 2;
	EatSomething(fTime);
}

void CPlayer::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutputDebugString(TEXT("Block\n"));
}
