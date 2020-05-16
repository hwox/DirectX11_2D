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
#include "Monster.h"
#include "..\Object\PlayerLife.h"
#include "Effect.h"
#include "MapObstacle.h"
#include "EffectSoundObj.h"
#include "..\InformationSave.h"



#define STAND_SCALE				130.f
#define JUMP_SCALE				200.f
#define MONSTERSPLIT_SCALE		350.f
#define EAT_SCALE				180.f
#define EATMONSTER_SCALE		160.f
#define INIT_YPOS				 230.f
#define STAND_MASS				1.f
#define FAT_MASS				10.f

#define STAND_SPEED				500.f

#define BEAM_ATTACK_X			300.f
#define BEAM_ATTACK_Y			600.f


CPlayer::CPlayer()
{
	m_pBody = nullptr;
	m_pAnimation = nullptr;
	m_pCamera = nullptr;
	m_pRotPivot = nullptr;
	m_pChild1Mesh = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;
	u_pLifeBar = nullptr;
	BackImage = nullptr;
	m_pMapBody = nullptr;
	m_KirbyState = 0;
	m_pEatMonster = nullptr;
	m_SaveState = 0;
	m_IsMove = true;

	///////////////// HP	 /////////////////
	m_pHP = MAX_HP;
	m_pLifeCount = 3;

	/////////////////   JUMP   /////////////////

	m_pMass = STAND_MASS;
	jump_time = 0.1f;
	press_time = 0.f;

	m_pHasMonster = false;
	m_pHasAir = false;
	m_pIsJumping = false;
	m_pNowEating = false;
	m_pCantGo = false;
	JumpAnimationChangeOnce = false;
	m_pInfo = nullptr;
}

CPlayer::~CPlayer()
{
	//SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pEatMonster);
	SAFE_RELEASE(BackImage);
	SAFE_RELEASE(u_pLifeBar);
	SAFE_RELEASE(m_pMapBody);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pChild1Mesh);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pInfo);
}

bool CPlayer::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	BackImage = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");
	m_pCamera = CreateComponent<CCameraComponent>("Camera");
	m_pBody = CreateComponent<CColliderRect>("PlayerBody");
	m_pMapBody = CreateComponent<CColliderRect>("PlayerMapBody");
	//m_pEffect = CreateComponent<CEffectComponent>("PlayerEffect");
	m_pInfo = CreateComponent<CInformationSave>("Info");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	u_pLifeBar = m_pScene->SpawnObject<CPlayerLife>();


	SetPlayerAnimation();


	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pMesh->AddChild(m_pMapBody, TR_POS);

	m_pBody->SetExtent(STAND_SCALE, STAND_SCALE);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);
	m_pBody->AddBlockCallback<CPlayer>(this, &CPlayer::StruckedByMonster);
	m_pBody->AddBeginOverlapCallback<CPlayer>(this, &CPlayer::BlockedByObstacleBegin);
	m_pBody->AddEndOverlapCallback<CPlayer>(this, &CPlayer::BlockedByObstacleEnd);
	m_pBody->SetCollisionProfile("Player");
	m_pBody->EnableOverlap(true);

	m_pMapBody->SetExtent(STAND_SCALE - 60.f, 50.f);
	m_pMapBody->SetPivot(0.5f, 0.f, 0.f);
	m_pMapBody->AddBlockCallback<CPlayer>(this, &CPlayer::OnTheMap);
	m_pMapBody->AddEndOverlapCallback<CPlayer>(this, &CPlayer::NotOnTheMap);
	m_pMapBody->SetCollisionProfile("PlayerMap");
	m_pMapBody->EnableOverlap(true);


	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pCamera, TR_POS);

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -6.f, -20.f);
	m_pCamera->SetCameraPosLimit(StageMinX, StageMaxX, StageMinY, StageMaxY);
	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);


	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pBottomY = INIT_YPOS;
	m_pMesh->SetRelativePos(1000.f, INIT_YPOS, 0.f);
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	Vector3 InitYPos(0, 250.f, 0.f);
	m_pMovement->SetGravityUse(InitYPos);

	PlayerKeySetting();

	m_pMovement->SetMoveSpeed(STAND_SPEED);

	CreateNotifyList();



	return true;
}

void CPlayer::Begin()
{
	CGameObject::Begin();


	if (!m_pInfo->GetInformationFromTXT(m_KirbyState, m_pHP, m_pLifeCount))
	{
		/*m_KirbyState = 0;
		m_pHP = 1000.f;
		m_pLifeCount = 3;*/
	}
	else
	{
		m_pAnimation->ChangeAnimation("KirbyDigest");
		u_pLifeBar->SetSkillTitle(m_KirbyState);
		u_pLifeBar->SetHP(m_pHP);
		u_pLifeBar->SetLifeCount(m_pLifeCount);
	}

	u_pLifeBar->SetSkillTitle(m_KirbyState);
}

void CPlayer::Update(float fTime)
{
	CGameObject::Update(fTime);

	pPos = GetWorldPos();

	//m_pRotPivot->AddRelativeRotationZ(180.f * fTime);

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



	//if (m_pNowEating)
	//{
	//	// 먹고 있는 상태라서 지금 그 구간 만들어야 하는 상태
	//	MakeAirZone(fTime);
	//}


	ComputeJump(fTime);


	CamLimit(fTime);
}

void CPlayer::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CPlayer::PlayerKeySetting()
{

	GET_SINGLE(CInput)->AddAxisKey("Move", DIK_RIGHT, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("Move", DIK_LEFT, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("Move", this, &CPlayer::MoveSide);

	//GET_SINGLE(CInput)->AddActionKey("Fire", DIK_SPACE);
	//GET_SINGLE(CInput)->BindAction<CPlayer>("Fire", AKS_PRESS, this, &CPlayer::Fire);

	////////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CInput)->AddAxisKey("DigestMonster", DIK_F, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("DigestMonster", this, &CPlayer::DigestMonster);


	////////////////////////////////////////////////////////////////////////////

	 // 기본 점프. 점프키는 cool time 존재 그니까 기본 A만 


	GET_SINGLE(CInput)->AddActionKey("JumpInput", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpInput", AKS_PUSH, this, &CPlayer::AKeyDown);

	GET_SINGLE(CInput)->AddActionKey("JumpEnd", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpEnd", AKS_RELEASE, this, &CPlayer::AKeyUp);


	////////////////////////////////////////////////////////////////////////////


	GET_SINGLE(CInput)->AddActionKey("Up", DIK_UP);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Up", AKS_PUSH, this, &CPlayer::UpKeyDown);

	GET_SINGLE(CInput)->AddActionKey("UpDouble", DIK_UP);
	GET_SINGLE(CInput)->BindAction<CPlayer>("UpDouble", AKS_DOUBLE, this, &CPlayer::UpKeyDoubleDown);

	////////////////////////////////////////////////////////////////////////////


	GET_SINGLE(CInput)->AddAxisKey("IdleKeyDown", DIK_DOWN, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("IdleKeyDown", this, &CPlayer::DownKey);


	////////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CInput)->AddActionKey("Blackhole", DIK_S);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Blackhole", AKS_PRESS, this, &CPlayer::SKeyDown);


	GET_SINGLE(CInput)->AddActionKey("BlackholeEnd", DIK_S);
	GET_SINGLE(CInput)->BindAction<CPlayer>("BlackholeEnd", AKS_RELEASE, this, &CPlayer::SKeyUp);

	////////////////////////////////////////////////////////////////////////////


	GET_SINGLE(CInput)->AddActionKey("SkillAttack", DIK_V);
	GET_SINGLE(CInput)->BindAction<CPlayer>("SkillAttack", AKS_PRESS, this, &CPlayer::Attack);



}

void CPlayer::SetPlayerAnimation()
{
	m_pAnimation->AddAnimation2DSequence("KirbyIdle");
	m_pAnimation->AddAnimation2DSequence("KirbyWalk");
	m_pAnimation->AddAnimation2DSequence("KirbyIdleDown");
	m_pAnimation->AddAnimation2DSequence("KirbyDown");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpEnd");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpIng");
	m_pAnimation->AddAnimation2DSequence("KirbyJump");
	m_pAnimation->AddAnimation2DSequence("KirbyEat");
	m_pAnimation->AddAnimation2DSequence("KirbyEatOver");
	m_pAnimation->AddAnimation2DSequence("KirbyDamage");
	m_pAnimation->AddAnimation2DSequence("KirbyDigestMonster");
	m_pAnimation->AddAnimation2DSequence("KirbyDigest");
	m_pAnimation->AddAnimation2DSequence("KirbySplitStar");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpUp");
	m_pAnimation->AddAnimation2DSequence("KirbyJumpDown");
	m_pAnimation->AddAnimation2DSequence("KirbyMonsterWalk");
	m_pAnimation->AddAnimation2DSequence("KirbyMonsterJump");
	m_pAnimation->AddAnimation2DSequence("KirbyMonsterJumpUp");
	m_pAnimation->AddAnimation2DSequence("KirbyMonsterIdle");


	////////////////////////////////////////////////////////////

	m_pAnimation->AddAnimation2DSequence("BeamJumpUp");
	m_pAnimation->AddAnimation2DSequence("BeamWalk");
	m_pAnimation->AddAnimation2DSequence("BeamJumpDown");
	m_pAnimation->AddAnimation2DSequence("BeamIdleDown");
	m_pAnimation->AddAnimation2DSequence("BeamIdle");
	m_pAnimation->AddAnimation2DSequence("BeamJumpIng");
	m_pAnimation->AddAnimation2DSequence("BeamDamage");
	m_pAnimation->AddAnimation2DSequence("BeamSplitAir");
	m_pAnimation->AddAnimation2DSequence("BeamAttack");
	m_pAnimation->AddAnimation2DSequence("BeamJumpEnd");


	////////////////////////////////////////////////////////////

	m_pAnimation->AddAnimation2DSequence("CutterAttack");
	m_pAnimation->AddAnimation2DSequence("CutterDigestion");	
	m_pAnimation->AddAnimation2DSequence("CutterJumpDown");
	m_pAnimation->AddAnimation2DSequence("CutterWalk");
	m_pAnimation->AddAnimation2DSequence("CutterSplitAir");
	m_pAnimation->AddAnimation2DSequence("CutterJumpIng");
	m_pAnimation->AddAnimation2DSequence("CutterJumpUp");
	m_pAnimation->AddAnimation2DSequence("CutterIdle");


}

void CPlayer::MoveSide(float fScale, float fTime)
{
	if (m_IsMove) {
		if (fScale != 0.f)
		{
			if (!JumpUp && !JumpDown) {
				if (!m_pHasAir /*&& !m_pNowEating*/ && !m_pHasMonster && !m_pIsAttack)
				{
					WalkStateAnimation();
				}
				else if (m_pHasMonster)
				{
					MonsterWalkStateAnimation();
				}
			}

			if (!m_pCantGo) {
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
			}
			else if (dir != fScale)
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
				m_pCantGo = false;
			}
			if (fScale < 0.f)
			{
				m_pMesh->SetRelativeRotationY(180.f);
				dir = -1;
			}
			else
			{
				m_pMesh->SetRelativeRotationY(0.f);
				dir = 1;
			}


		}

		else
		{
			if (!JumpUp && !JumpDown) {
				if (!m_pHasAir && !m_pNowEating && !m_pHasMonster && !m_pIsAttack)
				{
					IdleStateAnimation();
				}
				else if (m_pHasMonster)
				{
					MonsterIdleStateAnimation();
				}
			}
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

	CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 60.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));
	pBullet->SetRelativeRotationY(m_pMesh->GetRelativeRot().y);
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

	m_SaveState = 0;

	m_pHasAir = false;
}

void CPlayer::FireEnd(float fTime)
{
	m_pIsAttack = false;
	m_IsMove = true;
	//	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	m_pNowEating = false;
}

void CPlayer::Attack(float fTime)
{
	if (!m_pIsJumping && !m_pHasAir && !m_pHasMonster && !m_pIsAttack && m_KirbyState != Stand)
	{
		// 공격
		m_pIsAttack = true;
		switch (m_KirbyState)
		{
		case Beam:
			m_pMesh->SetRelativeScale(BEAM_ATTACK_X, BEAM_ATTACK_Y, 1.f);
			m_pAnimation->ChangeAnimation("BeamAttack");
			SetWorldPos(pPos - Vector3(0.f, 250.f, 0.f));
			m_pBody->SetRelativePos(60.f, 250.f, 0.f);
			m_pHasMonster = false;
			m_pNowEating = false;  // 그냥 한 번 더 해주는중 
			break;
		case Cutter:
			m_pAnimation->ChangeAnimation("CutterAttack");
			m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);


			CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 150.f,
				Vector3(0.f, 0.f, GetRelativeRot().z));
			pBullet->SetRelativeRotationY(m_pMesh->GetRelativeRot().y);
			pBullet->SetBulletType(1);

			SAFE_RELEASE(pBullet);

			m_pHasMonster = false;
			m_pNowEating = false;  // 그냥 한 번 더 해주는중 
			break;
		}
	}
}

void CPlayer::DownKey(float fScale, float fTime)
{
	static bool	bMove = false;

	if (!m_pHasMonster)
	{
		if (fScale != 0.f)
		{
			bMove = true;
			if (!m_pHasAir)
			{
				if (IsPlayAnimation) {
					IdleDownStateAnimation();
					OutputDebugString(TEXT("들어오면 안되는 곳 \n"));
				}
			}
			else
			{
				if (IsPlayAnimation) {

					m_pHasAir = false;
					m_pMass = STAND_MASS;
					DisablePlayAnimation(fTime);


					m_pAnimation->ChangeAnimation("KirbyDigest");
					m_pAnimation->SetReturnSequenceName("KirbyDigest", "KirbyIdle");

				}
			}
		}
		else
		{
			if (bMove)
			{
				IdleStateAnimation();
				bMove = false;
			}
		}
	}

}

void CPlayer::ReturnToIdle(float fTime)
{
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	IdleStateAnimation();
	m_IsMove = true;
}

void CPlayer::ReturnToMonsterIdle(float fTime)
{
	m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
	MonsterIdleStateAnimation();
}

void CPlayer::EnableMove(float fTime)
{
	m_IsMove = true;
	m_pMovement->BackStepEnd();
}

void CPlayer::DisableMove(float fTime)
{
	m_IsMove = false;
}

void CPlayer::SKeyDown(float fTime)
{
	if (/*!m_pIsJumping && */!m_pHasAir && !m_pHasMonster && !m_pIsAttack)
	{
		// 기본 공기흡입
		if (!m_pNowEating)
		{
			m_pAnimation->ChangeAnimation("KirbyEat");
			m_pNowEating = true;
			m_pMesh->SetRelativeScale(EAT_SCALE, EAT_SCALE, 1.f);

			m_pBody->SetExtent(800.f, STAND_SCALE);
		}
	}
	else
	{
		if (m_pHasAir)
		{
			// 공기 뱉기
			SpitAir(fTime);
			return;
		}
		if (m_pHasMonster)
		{
			m_pIsAttack = true;
			m_pMesh->SetRelativeScale(MONSTERSPLIT_SCALE, STAND_SCALE, 1.f);
			m_pAnimation->ChangeAnimation("KirbySplitStar");

			m_pHasMonster = false;
			m_pNowEating = false;  // 그냥 한 번 더 해주는중 
			return;
		}
		if (m_pIsJumping)
		{
			//점프중에 S
			// 공기 뱉어야 함
			SpitAir(fTime);
		}
	}
}

void CPlayer::SKeyUp(float fTime)
{
	if (m_pHasMonster) {

	}
	else if (m_pHasAir)
	{
		//m_pAnimation->ChangeAnimation("KirbyEatOver");
		////m_pAnimation->SetReturnSequenceName("KirbyEatOver", "KirbyIdle");
		//m_pAnimation->CreateNotify("KirbyEatOver", "SetHasAirFalse", 3);
		//m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "SetHasAirFalse", this, &CPlayer::SetHasAirFalse);
		//m_IsMove = false;
	}
	else if (m_pNowEating)
	{
		if (!m_pIsAttack) {
			m_pBody->SetExtent(STAND_SCALE, STAND_SCALE);


			m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
			m_pAnimation->ChangeAnimation("KirbyEatOver");
			//m_pAnimation->CreateNotify("KirbyEatOver", "EatAirFail", 3);
			//m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "EatAirFail", this, &CPlayer::EatAirFail);
			//m_IsMove = false;


			Vector3 Temp = pPos;
			Temp.x += 50.f;
			CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(Temp,
				Vector3(0.f, 0.f, 0.f));
			pEffect->Effect_SplitAir();
			SAFE_RELEASE(pEffect);

		}
	}
}

void CPlayer::AKeyDown(float fTime)
{
	if (press_time < JUMP_AMOUNT + 10.f)
	{
		m_pMovement->SetMoveSpeed(700.f);
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * m_pMass);
		press_time += (fTime)*20.f;
		JumpUp = true;
		if (!JumpAnimationChangeOnce) {
			if (!m_pHasMonster && !m_pHasAir)
			{
				JumpUpStateAnimation();
				JumpAnimationChangeOnce = true;
			}
			else if (m_pHasMonster)
			{
				MonsterJumpUpStateAnimation();
				JumpAnimationChangeOnce = true;
			}
		}
	}
	else
	{
		// 하다가 그 뭐야 거기 
		// 발판같은거 충돌 만드는 그 코드에다가 
		// 이거 다 초기화 시키는 부분 추가해
		// 함수로 모듈화 해가지고 붙여넣게
		m_pMovement->SetMoveSpeed(STAND_SPEED);
		JumpUp = false;
		JumpDown = true;
	}


	if (!m_pIsJumping)
	{
		m_pIsJumping = true;
	}
	else if (m_pIsJumping)
	{
		if (m_pHasAir)
		{
			// 위로 누를 수록 점프

		}
		else if (!m_pHasAir)
		{

		}

	}

}

void CPlayer::AKeyUp(float fTime)
{
	JumpDown = true;
}

void CPlayer::UpKeyDown(float fTime)
{
	// 여기는 그냥 air 상태거나 그럴 때 위로 가는  용도로만
	if (m_pIsJumping || m_pHasAir)
	{
		//	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * m_pMass);
		//	press_time += (fTime)*20.f;
	}

	JumpDown = true;
}

void CPlayer::UpKeyDoubleDown(float fTime)
{
	if (!m_pHasAir)
	{
		JumpIngStateAnimation();
		m_pHasAir = true;
		m_pMass = FAT_MASS;
		m_pMesh->SetRelativeScale(EAT_SCALE, EAT_SCALE, 1.f);
	}
}


void CPlayer::SpitAir(float fTime)
{
	m_pAnimation->ChangeAnimation("KirbyEatOver");

	Vector3 Temp = pPos;
	pPos.x = 50.f;
	CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(Temp,
		Vector3(0.f, 0.f, 0.f));
	pEffect->Effect_SplitAir();
	SAFE_RELEASE(pEffect);

	m_pMass = STAND_MASS;
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	m_pNowEating = false;
	//	m_pHasAir = false;
}


void CPlayer::EatAirFail(float fTime)
{
	IdleStateAnimation();
	m_pNowEating = false;
	m_IsMove = true; // 이거 하는동안에 움직이지 말라고 
	m_pHasAir = false;
	m_pIsJumping = false; // 추가된거 이거 
	OutputDebugString(TEXT("Eat Air False 호출 \n"));
}


void CPlayer::EatMonsterSuccess()
{
	m_pFishingMonster = true;

}

void CPlayer::ComputeJump(float fTime)
{

	if (!JumpDown)
		return;

	//if (pPos.y >= INIT_YPOS ) // 나중에 땅바닥에 뭐 밟고 있는지로 체크해
	if (press_time >= 0.f)
	{
		if (!m_pIsFootOnFloor) {
			m_pMovement->SetMoveSpeed(700.f);
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * -m_pMass);
			press_time -= (fTime)*20.f;
			if (JumpAnimationChangeOnce) {
				if (!m_pHasMonster && !m_pHasAir)
				{
					JumpDownStateAnimation();
				}
				else if (m_pHasMonster)
				{
					MonsterJumpDownStateAnimation();
				}
				JumpAnimationChangeOnce = false;
			}
		}
		else if (m_pIsFootOnFloor)
		{
			JumpEnd();
		}
	}
	else
	{
		if (!m_pIsFootOnFloor)
		{
			press_time += 1.f;
			return;
		}
		JumpEnd();
	}
}

void CPlayer::JumpEnd()
{
	JumpDown = false;
	JumpUp = false;
	press_time = 0;
	SetWorldPos(pPos.x, m_pBottomY, pPos.z);
	m_pMovement->SetMoveSpeed(STAND_SPEED);

}

void CPlayer::ApplySkill(int state)
{
	m_KirbyState = state;
	switch (state)
	{
	case Stand:
		OutputDebugString(TEXT("Skill Input 0, Something has problem"));
		break;
	case Beam:
		//1
		OutputDebugString(TEXT("Skill Input 1"));


		break;
	case Cutter:
		//2
		break;
	case Ice:
		break;
	}
}

void CPlayer::StarAttack(float fTime)
{
}

void CPlayer::DigestMonster(float fScale, float fTime)
{
	if (fScale != 0 && m_SaveState != 0) {
		if (m_pHasMonster)
		{
			m_pAnimation->ChangeAnimation("KirbyDigest");
			m_pHasMonster = false;
			m_KirbyState = m_SaveState;
			m_SaveState = 0;
			m_pNowEating = false;
			m_IsMove = false;

			u_pLifeBar->SetSkillTitle(m_KirbyState);
		}
	}
}

void CPlayer::CamLimit(float fTime)
{

	//흠 끝에 X 막는건 왜 안되는지 

	Vector3 camPos = m_pCamera->GetWorldPos();
	Vector3 playerPos = GetWorldPos();

	if (playerPos.y + _RESOLUTION.iHeight / 1.5f >= StageMaxY /*+ _RESOLUTION.iHeight / -6.f*/)
	{

		float temp = _RESOLUTION.iHeight / 1.5f;
		temp += playerPos.y;
		m_pCamera->SetDontComputeCamY(true);

		temp = playerPos.x + _RESOLUTION.iWidth / 2.f;
		if (playerPos.x + _RESOLUTION.iWidth / 2.f >= StageMaxX ||
			playerPos.x - _RESOLUTION.iWidth / 2.f <= StageMinX)
		{
			m_pCamera->SetDontComputeCamX(true);
		}
		else
		{
			m_pCamera->SetDontComputeCamX(false);
		}


	}
	else
	{
		m_pCamera->SetDontComputeCamY(false);
		if (playerPos.x + _RESOLUTION.iWidth / 2.f >= StageMaxX ||
			playerPos.x - _RESOLUTION.iWidth / 2.f <= StageMinX)
		{
			m_pCamera->SetDontComputeCamX(true);
		}
		else
		{
			m_pCamera->SetDontComputeCamX(false);
		}

	}

}

void CPlayer::SetStageMinMax(float minx, float maxx, float miny, float maxy)
{
	StageMinX = minx;
	StageMaxX = maxx;
	StageMinY = miny;
	StageMaxY = maxy;
}

void CPlayer::WalkStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyWalk");
		m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		m_pBody->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		break;
	case Beam:
		m_pAnimation->ChangeAnimation("BeamWalk");
		m_pMesh->SetRelativeScale(STAND_SCALE + 20.f, STAND_SCALE + 20.f, 1.f);
		m_pBody->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		break;
	case Cutter:
		m_pAnimation->ChangeAnimation("CutterWalk");
		m_pMesh->SetRelativeScale(STAND_SCALE + 20.f, STAND_SCALE + 20.f, 1.f);
		m_pBody->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}

	m_pNowEating = false;
}

void CPlayer::MonsterWalkStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyMonsterWalk");
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
		m_pBody->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
		break;
	case Beam:
		break;
	case Cutter:
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}

	m_pNowEating = false;
}

void CPlayer::IdleStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		m_pAnimation->ChangeAnimation("KirbyIdle");
		break;
	case Beam:
		m_pMesh->SetRelativeScale(STAND_SCALE + 20.f, STAND_SCALE + 20.f, 1.f);
		m_pAnimation->ChangeAnimation("BeamIdle");
		break;
	case Cutter:
		m_pMesh->SetRelativeScale(STAND_SCALE + 20.f, STAND_SCALE + 20.f, 1.f);
		m_pAnimation->ChangeAnimation("CutterIdle");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::MonsterIdleStateAnimation()
{
	//	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	switch (m_KirbyState)
	{
	case Stand:
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
		m_pBody->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
		m_pAnimation->ChangeAnimation("KirbyMonsterIdle");
		break;
	case Beam:
		break;
	case Cutter:
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::IdleDownStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyIdleDown");
		break;
	case Beam:
		m_pAnimation->ChangeAnimation("BeamIdleDown");
		break;
	case Cutter:
		//m_pAnimation->ChangeAnimation("KirbyIdleDown");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::JumpDownStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyJumpDown");
		m_pAnimation->SetReturnSequenceName("KirbyJumpDown", "KirbyIdle");
		break;
	case Beam:
		m_pAnimation->ChangeAnimation("BeamJumpDown");
		m_pAnimation->SetReturnSequenceName("BeamJumpDown", "BeamIdle");
		break;
	case Cutter:
		m_pAnimation->ChangeAnimation("CutterJumpDown");
		m_pAnimation->SetReturnSequenceName("CutterJumpDown", "CutterIdle");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::MonsterJumpDownStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyMonsterJump");
		m_pAnimation->SetReturnSequenceName("KirbyMonsterJump", "KirbyMonsterIdle");
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE, 1.f);
		break;
	case Beam:
		break;
	case Cutter:
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::JumpUpStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyJumpUp");
		break;
	case Beam:
		m_pAnimation->ChangeAnimation("BeamJumpUp");
		break;
	case Cutter:
		m_pAnimation->ChangeAnimation("CutterJumpUp");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::MonsterJumpUpStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE*1.2, 1.f);
		m_pAnimation->ChangeAnimation("KirbyMonsterJumpUp");
		break;
	case Beam:

		break;
	case Cutter:
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::DamageStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pAnimation->ChangeAnimation("KirbyDamage");
		m_pAnimation->SetReturnSequenceName("KirbyDamage", "KirbyIdle");

		//m_pAnimation->CreateNotify("KirbyDamage", "DamageEnd", 7);
		//m_pAnimation->AddNotifyFunction<CPlayer>("KirbyDamage", "DamageEnd", this, &CPlayer::EnableMove);
		break;
	case Beam:

		m_pAnimation->ChangeAnimation("BeamDamage");
		m_pAnimation->SetReturnSequenceName("BeamDamage", "BeamIdle");

		break;
	case Cutter:
		////m_pAnimation->ChangeAnimation("BeamDamage");
		//m_pAnimation->SetReturnSequenceName("BeamDamage", "CutterIdle");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::JumpIngStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE*1.2, 1.f);
		m_pAnimation->ChangeAnimation("KirbyJumpIng");
		break;
	case Beam:
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE*1.2, 1.f);
		m_pAnimation->ChangeAnimation("BeamJumpIng");
		break;
	case Cutter:
		m_pMesh->SetRelativeScale(EATMONSTER_SCALE, EATMONSTER_SCALE*1.2, 1.f);
		m_pAnimation->ChangeAnimation("CutterJumpIng");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}
}

void CPlayer::DigestionStateAnimation()
{
	switch (m_KirbyState)
	{
	case Stand:
		m_pMesh->SetRelativeScale(STAND_SCALE * 2.5f, STAND_SCALE, 1.f);
		m_pAnimation->ChangeAnimation("KirbyDigestMonster");
		break;
	case Beam:

		break;
	case Cutter:
		m_pMesh->SetRelativeScale(STAND_SCALE * 2.5f, STAND_SCALE, 1.f);
		m_pAnimation->ChangeAnimation("CutterDigestion");
		break;
	case Ice:
		break;
	default:
		OutputDebugString(TEXT("State : Something wrong"));
	}


}

void CPlayer::EnablePlayAnimation(float fTime)
{
	IsPlayAnimation = false;
}

void CPlayer::DisablePlayAnimation(float fTime)
{
	IsPlayAnimation = true;
}

void CPlayer::AfterBeamAttack(float fTime)
{
	OutputDebugString(TEXT("Beam Attack"));
	
	IdleStateAnimation();
	m_pIsAttack = false;
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	SetWorldPos(pPos + Vector3(0.f, 250.f, 0.f));
	m_pBody->SetRelativePos(0.f, 0.f, 0.f);
}

void CPlayer::AfterCutterAttack(float fTime)
{
	OutputDebugString(TEXT("Cutter Attack"));
	IdleStateAnimation();

	m_pIsAttack = false;

}


void CPlayer::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutputDebugString(TEXT("Block\n"));

	//m_IsMove = false;

	// 현재 가고 있는 방향 반대면 입력 들어올 수 있게 해야 함
}

void CPlayer::BlockedByObstacleBegin(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr)
		return;
	if (pDest->GetCollisionProfile()->strName == "MapObject"
		|| pDest->GetCollisionProfile()->strName == "MapBlock")
	{
		if (!m_pCantGo) {
			m_pCantGo = true;
		}
		return;
	}

}

void CPlayer::BlockedByObstacleEnd(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr || pDest->IsActive() == false)
		return;
	if (pDest->GetCollisionProfile()->strName == "MapObject" ||
		pDest->GetCollisionProfile()->strName == "MapBlock")
	{
		m_pCantGo = false;
	}
}

void CPlayer::StruckedByMonster(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

	if (pDest == nullptr || pDest->IsActive() == false) 
		return;

	if (pDest->GetCollisionProfile()->strName == "MapObject"||
		pDest->GetCollisionProfile()->strName == "MapBlock")
	{
		return;
	}

	if (pDest->GetName() == "MapBlockBody")
	{
		// Star 먹은걸로... setting 

		return; 
	}

	if (pDest->GetCollisionProfile()->strName == "Item")
	{
		// 아이템 먹은거

		// effect 
		m_pHP += 100;

		if (m_pHP > 0 && m_pHP < MAX_HP) {
			u_pLifeBar->SetHP(m_pHP);
		}
		else if(m_pHP >= MAX_HP)
		{
			m_pHP = 100;
			u_pLifeBar->SetHP(m_pHP);
			u_pLifeBar->SetLifeCount(++m_pLifeCount);
		}

		pDest->GetOwner()->Kill();
		return; 
	}

	if (pDest->GetCollisionProfile()->strName == "Monster") {
		if (m_pIsAttack)
		{
			// 주거라 ㅡㅡ 
			CMonster*	pMonster = (CMonster*)(pDest->GetOwner());
			pMonster->SetAttackedBySkill(true);
			OutputDebugString(TEXT("Map Obstacle \n"));
			//	SAFE_RELEASE(pMonster);

			return;
		}

		if (m_pNowEating)
		{

			m_pBody->SetExtent(STAND_SCALE, STAND_SCALE);
			// 그리고 그 함수에서 animation 실행

			//SAFE_RELEASE(m_pEat);
			if (m_pFishingMonster)
			{
				// 들어와서 충돌됨 
				m_pEatMonster->Enable(false);
				m_pHasMonster = true;
				DigestionStateAnimation();

				m_SaveState = m_pEatMonster->GetSkillType();

				m_pFishingMonster = false;
				m_pEatMonster->SetEatingEnd(true);
				//m_pNowEating = false; 
				return;
			}
			m_pEatMonster = (CMonster*)(pDest->GetOwner());
			m_pEatMonster->SetIsEating(true);


			// 함수 호출 !빨아들이는!
			EatMonsterSuccess();
			// eat_skill 전달

			OutputDebugString(TEXT("Collision With Monster \n"));
		}
		else if (!m_pNowEating)
		{
			m_pHP -= 100;

			if (m_pHP > 0) {
				u_pLifeBar->SetHP(m_pHP);
			}
			else
			{
				m_pHP = MAX_HP;
				u_pLifeBar->SetHP(m_pHP);
				u_pLifeBar->SetLifeCount(m_pLifeCount--);
			}
			DisableMove(fTime);

			CEffectSoundObj*	pFireSound = m_pScene->SpawnObject<CEffectSoundObj>(GetWorldPos(),
				Vector3(0.f, 0.f, GetRelativeRot().z));

			pFireSound->SetSound("DamagedByMonster", "Effect\\Real_Damaged.wav");

			SAFE_RELEASE(pFireSound);

			DamageStateAnimation();

			m_pMovement->BackStep(GetWorldAxis(AXIS_X));
		}
	}
}

void CPlayer::NotOnTheMap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// 맵에서 발바닥 뗌
	if (pDest == nullptr)
		return;
	m_pIsJumping = true;
	m_pIsFootOnFloor = false;

	if (!JumpUp)
	{
		JumpDown = true; 
		if (!m_pHasMonster && !m_pHasAir)
		{
			JumpDownStateAnimation();
		}
		else if (m_pHasMonster)
		{
			MonsterJumpDownStateAnimation();
		}
	}
}

void CPlayer::OnTheMap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// 맵바닥에 발 붙이고 있는 상태
	if (pDest == nullptr)
		return;
	m_pBottomY = GetWorldPos().y;

	m_pIsJumping = false;
	int random = rand() % 360 + 1;
	m_pIsFootOnFloor = true;


	Vector3 Temp = pPos;
	Temp.x += 90.f;
	CEffect*	pEffect = m_pScene->SpawnObject<CEffect>(pPos, Vector3(0.f, 0.f, 180.f));
	pEffect->SetEffectRotationY(m_pMesh->GetRelativeRot().y);
	pEffect->Effect_JumpEffect();
	SAFE_RELEASE(pEffect);
}

void CPlayer::CreateNotifyList()
{
	m_pAnimation->CreateNotify("KirbyEatOver", "EatAirFail", 3);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "EatAirFail", this, &CPlayer::EatAirFail);

	m_pAnimation->CreateNotify("KirbyEat", "EatOver", 14);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEat", "EatOver", this, &CPlayer::SKeyUp);


	m_pAnimation->CreateNotify("KirbySplitStar", "AttackStar", 3);
	m_pAnimation->AddNotifyFunction("KirbySplitStar", "AttackStar", this, &CPlayer::Fire);
	m_pAnimation->CreateNotify("KirbySplitStar", "AttackStarEnd", 12);
	m_pAnimation->AddNotifyFunction("KirbySplitStar", "AttackStarEnd", this, &CPlayer::FireEnd);


	m_pAnimation->CreateNotify("KirbyDigest", "ChangeToIdle", 5);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyDigest", "ChangeToIdle", this, &CPlayer::ReturnToIdle);

	m_pAnimation->CreateNotify("KirbyDigestMonster", "ChangeToMonsterIdle", 7);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyDigestMonster", "ChangeToMonsterIdle", this, &CPlayer::ReturnToMonsterIdle);

	m_pAnimation->CreateNotify("CutterDigestion", "CutterChangeToMonsterIdle", 3);
	m_pAnimation->AddNotifyFunction<CPlayer>("CutterDigestion", "CutterChangeToMonsterIdle", this, &CPlayer::ReturnToMonsterIdle);

	m_pAnimation->CreateNotify("KirbyDamage", "DamageEnd", 7);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyDamage", "DamageEnd", this, &CPlayer::EnableMove);


	m_pAnimation->CreateNotify("BeamDamage", "BeamDamageEnd", 14);
	m_pAnimation->AddNotifyFunction<CPlayer>("BeamDamage", "BeamDamageEnd", this, &CPlayer::EnableMove);


	m_pAnimation->CreateNotify("BeamAttack", "BeamAttackEnd", 34);
	m_pAnimation->AddNotifyFunction<CPlayer>("BeamAttack", "BeamAttackEnd", this, &CPlayer::AfterBeamAttack);

	m_pAnimation->CreateNotify("CutterAttack", "CutterAttackEnd", 5);
	m_pAnimation->AddNotifyFunction<CPlayer>("CutterAttack", "CutterAttackEnd", this, &CPlayer::AfterCutterAttack);
}

float CPlayer::Lerp(float value1, float value2, float amount)
{
	return float((1 - amount)*value1 + amount * value2);
}

void CPlayer::SetPlayerInfo()
{
	m_pInfo->GetPlayerInformation(m_KirbyState, m_pHP, m_pLifeCount);
	m_pInfo->SetInformationToTXT();
}

