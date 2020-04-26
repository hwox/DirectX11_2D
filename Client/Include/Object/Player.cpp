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



#define STAND_SCALE		170.f
#define JUMP_SCALE		210.f
#define EAT_SCALE		190.f
#define INIT_YPOS		 250.f
#define STAND_MASS		1.f
#define FAT_MASS		10.f

CPlayer::CPlayer()
{
	m_pBody = nullptr;
	m_pAnimation = nullptr;
	m_pCamera = nullptr;
	m_pRotPivot = nullptr;
	m_pChild1Mesh = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;
	m_Zone = nullptr;
	m_pLifeBar = nullptr;
	BackImage = nullptr;
	m_pMapBody = nullptr;
	//m_pEffect = nullptr;

	EatProcess = 0;
	IsAirMouse = false;
	m_KirbyState = 0;


	m_IsMove = true;

	///////////////// HP	 /////////////////
	m_pHP = MAX_HP;
	m_pLifeCount = 3;

	/////////////////   JUMP   /////////////////
	m_pJumpEnable = true;
	m_pMass = STAND_MASS;
	g = 1.f;
	jump_time = 0.1f;
	press_time = 0.f;
	jump_temp = 0.f;


	m_pHasMonster = false;
	m_pHasAir = false;
	m_pIsJumping = false;
	m_pNowEating = false;

}

CPlayer::~CPlayer()
{
	SAFE_RELEASE(m_Zone);
	//SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(BackImage);
	SAFE_RELEASE(m_pLifeBar);
	SAFE_RELEASE(m_pMapBody);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pChild1Mesh);
	SAFE_RELEASE(m_pMesh);
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

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pLifeBar = m_pScene->SpawnObject<CPlayerLife>();


	SetPlayerAnimation();


	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(200.f, 200.f);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);
	m_pBody->AddBlockCallback<CPlayer>(this, &CPlayer::StruckedByMonster);
	m_pBody->SetCollisionProfile("Player");

	m_pMapBody->AddBeginOverlapCallback<CPlayer>(this, &CPlayer::OnTheMap);
	m_pMapBody->AddEndOverlapCallback<CPlayer>(this, &CPlayer::NotOnTheMap);
	m_pMapBody->SetCollisionProfile("PlayerMap");

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
	//	m_pCamera->SetRelativePos(0.f,0.f, -20.f);


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);


	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);


	m_pMesh->SetRelativePos(1000.f, 250.f, 0.f);
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	Vector3 InitYPos(0, 250.f, 0.f);
	m_pMovement->SetGravityUse(InitYPos);

	PlayerKeySetting();


	return true;
}

void CPlayer::Begin()
{
	CGameObject::Begin();
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

	if (m_pNowEating)
	{
		// 먹고 있는 상태라서 지금 그 구간 만들어야 하는 상태
		MakeAirZone(fTime);
	}

	if (m_pIsJumping)
	{
		ComputeJump(fTime);
	}


	//CamLimit(fTime);
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

	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_SPACE);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Fire", AKS_PRESS, this, &CPlayer::Fire);



	////////////////////////////////////////////////////////////////////////////

	 // 기본 점프. 점프키는 cool time 존재 그니까 기본 A만 


	GET_SINGLE(CInput)->AddActionKey("JumpInput", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpInput", AKS_PUSH, this, &CPlayer::AKeyDown);

	GET_SINGLE(CInput)->AddActionKey("JumpEnd", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpEnd", AKS_RELEASE, this, &CPlayer::AKeyUp);

	// 짧게 두번 먹었으면 공기먹은 상태 됨 
	// 혹은 점프중에 착ㄱ지 안했는데 A 한번 더 누르면 공기먹은 상태로 바뀌고 착지

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

	GET_SINGLE(CInput)->AddActionKey("DeleteChild", DIK_RETURN);
	GET_SINGLE(CInput)->BindAction<CPlayer>("DeleteChild", AKS_PRESS, this, &CPlayer::Delete);

	GET_SINGLE(CInput)->AddActionKey("AttackSpeedUp", DIK_1);
	GET_SINGLE(CInput)->BindAction<CPlayer>("AttackSpeedUp", AKS_PRESS, this, &CPlayer::AttackSpeedUp);
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
}

void CPlayer::MoveSide(float fScale, float fTime)
{

	if (m_IsMove) {
		if (fScale != 0.f)
		{
			if (!m_pHasAir /*&& !m_pNowEating*/)
			{
				m_pAnimation->ChangeAnimation("KirbyWalk");

			}
			if (fScale < 0.f)
				m_pMesh->SetRelativeRotationY(180.f);

			else
				m_pMesh->SetRelativeRotationY(0.f);

			m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
		}

		else
		{
			if (!m_pHasAir && !m_pNowEating)
			{
				m_pAnimation->ChangeAnimation("KirbyIdle");
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

	//CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
	//	Vector3(0.f, 0.f, GetRelativeRot().z));

	//CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	//pMovement->SetDistance(500.f);

	//SAFE_RELEASE(pMovement);

	//CColliderRect* pBody = pBullet->GetBody();

	//pBody->SetCollisionProfile("PlayerProjectile");

	//SAFE_RELEASE(pBullet);

	//CEffectSoundObj*	pFireSound = m_pScene->SpawnObject<CEffectSoundObj>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
	//	Vector3(0.f, 0.f, GetRelativeRot().z));

	//pFireSound->SetSound("Demasia", "Demasia.mp3");

	//SAFE_RELEASE(pFireSound);
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
	CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		GetRelativeRot());

	CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	pMovement->SetDistance(500.f);

	SAFE_RELEASE(pMovement);

	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(pBullet);
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

	if (!HasMonster)
	{
		if (fScale != 0.f)
		{
			bMove = true;
			if (!IsAirMouse)
			{
				m_pAnimation->ChangeAnimation("KirbyIdleDown");
			}
			else
			{
				m_pAnimation->ChangeAnimation("KirbyDigest");
				m_pAnimation->SetReturnSequenceName("KirbyDigest", "KirbyIdle");
				IsAirMouse = false;
				m_pMass = STAND_MASS;
			}
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
	else
	{
		// 스킬 변화 
		// ChangeSkill(m_KirbyState);
	}
}

void CPlayer::ReturnToIdle(float fTime)
{
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
	m_pAnimation->ChangeAnimation("KirbyIdle");
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


void CPlayer::EatIng()
{
	// 여기가 몬스터 빨아들이는 부분

	// 충돌체 하나 앞에 붙여놓기
	//그 충돌체랑 몬스터랑 부딪히면 나한테 오고 (몇 초 동안)
	// 그 초 끝나면 나 돼지 되는거임 다시 air

	if (m_Zone == nullptr)
	{
		m_Zone = CreateComponent<CColliderRect>("AirZone");
		m_Zone->AddBlockCallback<CPlayer>(this, &CPlayer::HitAirZone);
		m_Zone->SetCollisionProfile("PlayerAirZone");
		m_pMesh->AddChild(m_Zone, TR_POS);

		if (GetRelativeRot().y == 0)
			m_Zone->SetRelativePos(200.f, 0.f, 0.f);
		else
			m_Zone->SetRelativePos(-200.f, 0.f, 0.f);

		m_Zone->SetExtent(250.f, 300.f);
		m_Zone->SetPivot(0.5f, 0.f, 0.f);

		m_pBody->AddBlockCallback<CPlayer>(this, &CPlayer::HitAirZone);
	}


}

void CPlayer::AKey(float fTime)
{
	if (!JumpIng)
	{
		// 이게 처음들어온거
		// 그니까 아예 점프아니고 아예 아무것도 안한상태
		JumpIng = true;
		m_pJumpEnable = false;
		FirstJump = true;
	}

	if (!FirstJump && JumpIng)
	{
		// jump는 하고 있지만 enable 은 true(손을 한번 뗀 상태면 두번째 입력이라고 봐도 무방하겠징?) 

		// 점프하고 있는 상태에서 Jump 키 한번 더  누르기
		if (!HasMonster)
		{
			m_pAnimation->ChangeAnimation("KirbyJump");
			m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		}
		else
		{
			// 여기는 monster 먹고 있는데 jump 리소스로 바꿔야 함
			m_pAnimation->ChangeAnimation("KirbyJump");
			m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		}

		m_pMass = STAND_MASS;
		IsAirMouse = true;
		m_pJumpEnable = false; // 점프 못해 이제 띄워야 하니까 
	}


	// press time 입력은 계속 press로 받고 
	if (press_time < JUMP_AMOUNT)
	{
		press_time += (fTime)*10.f;
		jump_time = press_time;
	}


	/*char buff[100];
	sprintf_s(buff, "press_time : %f \n", press_time);
	OutputDebugStringA(buff);*/
}

void CPlayer::JumpUpdate(float fTime)
{

	if (/*jump_time > 0.f*/ JumpIng)
	{
		if (!IsAirMouse)
		{
			//if (!m_pJumpEnable) {
			if (jump_time > 0 && jump_time <= JUMP_AMOUNT)
			{
				float tempY = jump_time + (g / m_pMass);
				m_pMovement->SetMoveSpeed(700.f);
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

				jump_time -= 0.1f;
				jump_temp += 0.1f;


				m_pAnimation->ChangeAnimation("KirbyJump");

				//char buff[100];
				//sprintf_s(buff, " Press 1  : %f \n", jump_time);
				//OutputDebugStringA(buff);
			}
			//}
			//else {
			else if (jump_time < 0 && jump_time >((-1)*jump_temp))
			{
				float tempY = jump_time + (g / m_pMass);
				m_pMovement->SetMoveSpeed(700.f);
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

				jump_time -= 0.1f;


			}
			else if (jump_time <= ((-1)*jump_temp) || pPos.y <= 130.f)
			{
				JumpIng = false;
				m_pMovement->SetMoveSpeed(500.f);
				//JumpInputEnd(fTime);
				pPos.y = 130.f;
				jump_time = 0.1f;
				press_time = 0.f;
				jump_temp = 0.f;
			}
			// 올라가다가 내려와야함  
		//}
		}
		else
		{
			// 내려올 필요 없음
			float tempY = jump_time + (g / m_pMass);
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);
			jump_time -= 0.05f;
		}

	}
}

void CPlayer::SKeyDown(float fTime)
{
	if (!m_pIsJumping && !m_pHasAir && !m_pHasMonster)
	{
		// 기본 공기흡입
		if (!m_pNowEating)
		{
			m_pAnimation->ChangeAnimation("KirbyEat");
			m_pAnimation->CreateNotify("KirbyEat", "EatOver", 14);
			m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEat", "EatOver", this, &CPlayer::SKeyUp);
			m_pNowEating = true;
			m_pMesh->SetRelativeScale(EAT_SCALE, EAT_SCALE, 1.f);
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
			// 공격
			// 공격함수 추가
			m_pAnimation->ChangeAnimation("KirbySplitStar");
			// 여기서 좌측 scale 증가시켜야 함 

			// 특정 frame에 fire 함수 등록시키고 

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
	if (m_pNowEating) {

		if (m_Zone != nullptr)
		{
			m_Zone->Enable(false);
			SAFE_RELEASE(m_Zone);
		}

		m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
		m_pAnimation->ChangeAnimation("KirbyEatOver");
		m_pAnimation->CreateNotify("KirbyEatOver", "EatAirFail", 3);
		m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "EatAirFail", this, &CPlayer::EatAirFail);
		m_IsMove = false;
	}
}

void CPlayer::AKeyDown(float fTime)
{

	if (!m_pIsJumping)
	{
		m_pIsJumping = true;
	}
	else if (m_pIsJumping)
	{
		if (press_time < JUMP_AMOUNT)
		{
			press_time += (fTime)*10.f;
			jump_time = press_time;
		}

		if (m_pHasAir)
		{
			// 위로 누를 수록 점프

		}
		else if (!m_pHasAir)
		{


		}

	}
	// 그리고 이거 jump 중인거는 그 바닥에 안 닿아 있으면 m_pIsJumping = true하는 걸로


}

void CPlayer::AKeyUp(float fTime)
{

}

void CPlayer::UpKeyDown(float fTime)
{
	/*if (!m_pIsJumping && !m_pNowEating && !m_pHasAir)
	{
		m_pAnimation->ChangeAnimation("KirbyJump");
		m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
	}*/

	// 여기는 그냥 air 상태거나 그럴 때 위로 가는  용도로만
	if (m_pIsJumping || m_pHasAir)
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * m_pMass);
	}


}

void CPlayer::UpKeyDoubleDown(float fTime)
{
	if (!m_pHasAir)
	{
		m_pAnimation->ChangeAnimation("KirbyJump");
		m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		m_pHasAir = true;
		m_pMass = FAT_MASS;
	}
}


void CPlayer::AKeyEnd(float fTime)
{
	// 여기 End는 Jump가 끝난 End가 아니라 JumpKeyInput이 끝난 상ㅌㅐ임
	// 그러니까 JumpIng 여기서 초기화하는거 아님
	m_pJumpEnable = true;

	//press_time = 0.f;
	FirstJump = false;
	//jump_time = 0.f;
}

void CPlayer::Up(float fTime)
{
	// 이 Mass는 공기 안먹은 상태면 다시 1로 ㅂㅏ꿔 줘야 함
	m_pMass = FAT_MASS;
	if (!IsAirMouse)
	{
		//  공기 먹은 상태 아니면 
		m_pAnimation->ChangeAnimation("KirbyJump");
		m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		IsAirMouse = true;
	}
	else
	{
		// 그냥 up up up up 

		// 이거 근데 풍선같이 해야 함

		// y만 따로 생각해서 풍선같이 하는거 하면 X로는 그냥 += 값만 넣어주면 됨 
	}
}

void CPlayer::ToEatAirState(float fTime)
{
}

void CPlayer::SpitAir(float fTime)
{
	m_pHasAir = false;
	m_pIsJumping = false;

	m_pAnimation->ChangeAnimation("KirbyJumpEnd");
	m_pAnimation->SetReturnSequenceName("KirbyJumpEnd", "KirbyIdle");

	m_pMass = STAND_MASS;
	m_pMesh->SetRelativeScale(STAND_SCALE, STAND_SCALE, 1.f);
}

void CPlayer::SplitStar(float fTime)
{
	if (HasMonster)
	{
		HasMonster = false;
		// 몬스터 있던거 날리는거니까

		// 뱉는거 별 날아가야 함 
		// 별 회전시키면서 날아가야댐 

		m_pAnimation->ChangeAnimation("KirbyEatOver");
		m_pAnimation->SetReturnSequenceName("KirbyEatOver", "KirbyIdle");
	}
}

void CPlayer::Yup(float fTime)
{
	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
}

void CPlayer::EatAirFail(float fTime)
{
	m_pAnimation->ChangeAnimation("KirbyIdle");
	m_pNowEating = false;
	m_IsMove = true; // 이거 하는동안에 움직이지 말라고 

	if (m_Zone != nullptr)
	{
		m_Zone->Enable(false);
		SAFE_RELEASE(m_Zone);
	}
}

void CPlayer::EatMonsterSuccess(float fTime)
{
}

void CPlayer::ComputeJump(float fTime)
{
	if (jump_time > 0 && jump_time <= JUMP_AMOUNT)
	{
		float tempY = jump_time + (g / m_pMass);
		m_pMovement->SetMoveSpeed(700.f);
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

		jump_time -= 0.1f;
		jump_temp += 0.1f;

		m_pAnimation->ChangeAnimation("KirbyJump");
	}
	else if (jump_time < 0 && jump_time >((-1)*jump_temp))
	{
		float tempY = jump_time + (g / m_pMass);
		m_pMovement->SetMoveSpeed(700.f);
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

		jump_time -= 0.1f;
	}
	else if (jump_time <= ((-1)*jump_temp) || pPos.y <= 130.f)
	{
		JumpIng = false;
		m_pMovement->SetMoveSpeed(500.f);
		pPos.y = 130.f;
		jump_time = 0.1f;
		press_time = 0.f;
		jump_temp = 0.f;
	}
}

void CPlayer::JumpEnd()
{
	// 두 가지 경우 같은데
	// 만약에 점프하다가 공기 먹는거 안할거면 하나임
	// 하지 말자

	m_pIsJumping = false;

}

void CPlayer::CamLimit(float fTime)
{
	//Vector3 camPos = m_pCamera->GetWorldPos();
	//Vector3 playerPos = GetWorldPos();

	//float tx = 0.f;
	//float ty = 0.f;

	//if (camPos.x - playerPos.x >= StageMinX /*+ _RESOLUTION.iWidth / 2*/)
	//{
	//	tx = camPos.x - playerPos.x;
	//}
	//else if (playerPos.x + camPos.x <= StageMaxX)
	//{
	//	tx = -(camPos.x - playerPos.x);
	//}
	//else
	//{
	//	tx = _RESOLUTION.iWidth / 2;
	//}

	//if (camPos.y - playerPos.y >= StageMinY /*+ _RESOLUTION.iHeight / -6.f*/)
	//{
	//	ty = -(playerPos.y - camPos.y);
	//}
	//else if (playerPos.y + camPos.y <= StageMaxY)
	//{
	//	ty = (playerPos.y - camPos.y);
	//}
	//else
	//{
	//	ty = _RESOLUTION.iHeight / -6.f;
	//}

	//m_pCamera->SetRelativePos(tx, ty, -20.f);



	Vector3 camPos = m_pCamera->GetWorldPos();
	Vector3 playerPos = GetWorldPos();

	float tx = 0.f;
	float ty = 0.f;

	if (camPos.x <= StageMinX)
	{
		tx = camPos.x;
	}
	else if (camPos.x >= StageMaxX)
	{
		tx =  camPos.x - StageMaxX;
	}

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / 2 - tx, _RESOLUTION.iHeight / -6.f + ty, -20.f);
}

void CPlayer::SetStageMinMax(float minx, float maxx, float miny, float maxy)
{
	StageMinX = minx;
	StageMaxX = maxx;
	StageMinY = miny;
	StageMaxY = maxy;
}

void CPlayer::MakeAirZone(float fTime)
{
	// 여기서 zone을 만드는데
	// 만약에 몬스터를 먹었으면
	// noweating= false;하고 
	// 캐릭터 애니메이션 바꾸고 (입에 뭐 들은 상태로)
	// m_pHasMonster = true; 

	if (m_Zone == nullptr)
	{
		m_Zone = CreateComponent<CColliderRect>("AirZone");
		m_Zone->AddBlockCallback<CPlayer>(this, &CPlayer::HitAirZone);
		m_Zone->SetCollisionProfile("PlayerAirZone");

		m_pMesh->AddChild(m_Zone, TR_POS);
		m_Zone->SetRelativePos(200.f, 0.f, 0.f);
		m_Zone->SetExtent(250.f, 300.f);
		m_Zone->SetPivot(0.5f, 0.f, 0.f);
	}

	if (m_pHasMonster)
	{
		// ㅇ만약에 m_Zone이 몬스터랑부딪히면 밑에 콜백함수로 들어오고
		// 그러면 거기서 hasmonster 가 true가 되니까 
		// 이제 이거 그만 체크하라고 makeairzone 을 돌리는 조건인 noweating을 false시키는거임
		m_pNowEating = false;


		// 
	}
}

void CPlayer::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutputDebugString(TEXT("Block\n"));

	//m_IsMove = false;

	// 현재 가고 있는 방향 반대면 입력 들어올 수 있게 해야 함
}

void CPlayer::StruckedByMonster(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	m_pHP -= 100;

	if (m_pHP > 0) {
		m_pLifeBar->SetHP(m_pHP);
	}
	else
	{
		m_pHP = MAX_HP;
		m_pLifeBar->SetHP(m_pHP);
		m_pLifeBar->SetLifeCount(m_pLifeCount--);
	}
	DisableMove(fTime);


	m_pAnimation->ChangeAnimation("KirbyDamage");
	m_pAnimation->SetReturnSequenceName("KirbyDamage", "KirbyIdle");

	m_pAnimation->CreateNotify("KirbyDamage", "DamageEnd", 7);
	m_pAnimation->AddNotifyFunction<CPlayer>("KirbyDamage", "DamageEnd", this, &CPlayer::EnableMove);

	m_pMovement->BackStep(GetWorldAxis(AXIS_X));
}

void CPlayer::HitAirZone(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// 몬스터 정보 받아오기
	if (!m_pHasMonster)
	{
		m_pHasMonster = true;

		// 애니메이션 바꾸고 
		//m_pAnimation->ChangeAnimation("KirbyJumpIng");
		//pDest->Enable(false);
		//pDest->Kill();
		m_IsMove = false;
		m_pNowEating = false;

		if (m_Zone != nullptr)
		{
			m_Zone->Enable(false);
			SAFE_RELEASE(m_Zone);
		}

		//흠 여기서 뭘 해야 하나?
	}
}

void CPlayer::NotOnTheMap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// 맵에서 발바닥 뗌
	m_pIsJumping = true;
}

void CPlayer::OnTheMap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// 맵바닥에 발 붙이고 있는 상태
	m_pIsJumping = false;
	OutputDebugString(TEXT("zzzzzz\n"));
}

float CPlayer::Lerp(float value1, float value2, float amount)
{
	return float((1 - amount)*value1 + amount * value2);
}

