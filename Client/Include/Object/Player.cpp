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


	EatProcess = 0;
	IsAirMouse = false;
	m_KirbyState = 0;
	m_pJumpEnable = true;
	m_pMass = 100.f;
	g = 1.f;
	jump_time = 0.f;
	press_time = 0.f;
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

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pCamera, TR_POS);

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f, -20.f);


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);


	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativePos(50.f, 50.f, 0.f);
	m_pMesh->SetRelativeScale(150.f, 150.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);


	GET_SINGLE(CInput)->AddAxisKey("Move", DIK_RIGHT, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("Move", DIK_LEFT, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("Move", this, &CPlayer::MoveSide);

	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_SPACE);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Fire", AKS_PRESS, this, &CPlayer::Fire);



	////////////////////////////////////////////////////////////////////////////

	 // �⺻ ����. ����Ű�� cool time ���� �״ϱ� �⺻ A�� 


	GET_SINGLE(CInput)->AddActionKey("JumpInput", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpInput", AKS_PUSH, this, &CPlayer::JumpInput);

	GET_SINGLE(CInput)->AddActionKey("JumpEnd", DIK_A);
	GET_SINGLE(CInput)->BindAction<CPlayer>("JumpEnd", AKS_RELEASE, this, &CPlayer::JumpInputEnd);

	// ª�� �ι� �Ծ����� ������� ���� �� 
	// Ȥ�� �����߿� ������ ���ߴµ� A �ѹ� �� ������ ������� ���·� �ٲ�� ����

	////////////////////////////////////////////////////////////////////////////


	GET_SINGLE(CInput)->AddActionKey("Up", DIK_UP);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Up", AKS_PUSH, this, &CPlayer::Up);


	////////////////////////////////////////////////////////////////////////////


	GET_SINGLE(CInput)->AddAxisKey("IdleKeyDown", DIK_DOWN, -1.f);
	GET_SINGLE(CInput)->BindAxis<CPlayer>("IdleKeyDown", this, &CPlayer::DownKey);


	////////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CInput)->AddActionKey("Blackhole", DIK_S);
	GET_SINGLE(CInput)->BindAction<CPlayer>("Blackhole", AKS_PRESS, this, &CPlayer::EatSomething);

	////////////////////////////////////////////////////////////////////////////
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


	JumpUpdate(fTime);
}

void CPlayer::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CPlayer::MoveSide(float fScale, float fTime)
{
	static bool	bMove = false;

	if (fScale != 0.f)
	{
		bMove = true;
		if (!IsAirMouse)
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
		if (bMove)
		{
			if (!IsAirMouse)
			{
				m_pAnimation->ChangeAnimation("KirbyIdle");
			}
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
	m_pMesh->SetRelativeScale(150.f, 150.f, 1.f);
	m_pAnimation->ChangeAnimation("KirbyIdle");
}

void CPlayer::EatSomething(float fTime)
{
	if (!IsAirMouse)
	{
		switch (EatProcess)
		{
		case 0:
			// ó�� �Դ���
			if (!EatAirIng)
			{
				EatAirIng = true;
				m_pAnimation->ChangeAnimation("KirbyEat");
				m_pAnimation->CreateNotify("KirbyEat", "EatOver", 14);
				m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEat", "EatOver", this, &CPlayer::EatSomethingEnd);
				EatProcess = 1;
				m_pMesh->SetRelativeScale(180.f, 180.f, 1.f);
			}
			//break; �Ϻη� break ���� �̸��� ���� �ϴϱ� 
		case 1:
			// �Դ��� 
			if (EatAirIng)
			{

			}
			break;
		case 2:
			if (EatAirIng)
			{
				EatAirIng = false;
				EatProcess = 0;
				m_pAnimation->ChangeAnimation("KirbyEatOver");
				m_pAnimation->CreateNotify("KirbyEatOver", "ReturnToIdle", 3);
				m_pAnimation->AddNotifyFunction<CPlayer>("KirbyEatOver", "ReturnToIdle", this, &CPlayer::ReturnToIdle);

			}
			break;
		default:
			OutputDebugString(TEXT("EatAir_Error\n"));
			break;
		}

		// �ٵ� ������ ���� �ѹ� ������ �ð� �� ���� ���� �ִ� �ٽ� S�� �ȵ� 
		// -> EatSomethingEnd�� Notify������ �����µ� ���� �׷����� if(EatAiring) �߰� ���༭ �ذ��� 
	}
	else
	{
		// ���� �Կ� �ְ� �ִ� ���̶� ���� ��
		SpitAir(fTime);
	}

}

void CPlayer::EatSomethingEnd(float fTime)
{
	if (EatAirIng) {

		EatProcess = 2;
		EatSomething(fTime);
	}
}

void CPlayer::JumpInput(float fTime)
{
	if (!JumpIng)
	{
		// �̰� ó�����°�
		// �״ϱ� �ƿ� �����ƴϰ� �ƿ� �ƹ��͵� ���ѻ���
		JumpIng = true;
		m_pJumpEnable = false;
		FirstJump = true;
	}

	if (!FirstJump && JumpIng)
	{
		// jump�� �ϰ� ������ enable �� true(���� �ѹ� �� ���¸� �ι�° �Է��̶�� ���� �����ϰ�¡?) 

		// �����ϰ� �ִ� ���¿��� Jump Ű �ѹ� ��  ������
		m_pAnimation->ChangeAnimation("KirbyJump");
		m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		m_pMesh->SetRelativeScale(180.f, 180.f, 1.f);
		m_pMass = 1000.f;
		IsAirMouse = true;
		IsJump = false;
		m_pJumpEnable = false; // ���� ���� ���� ����� �ϴϱ� 
	}


	// press time �Է��� ��� press�� �ް� 
	if (press_time < JUMP_AMOUNT)
	{
		press_time += (fTime)*5.f;
		jump_time += fTime * 5.f;
	}
	//else
	//{
	//	m_pJumpEnable = true;
	//}


	//	PrevPos = GetWorldPos(); // ó�� �޾ƿ��� 

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
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

				jump_time -= 0.1f;

				char buff[100];
				sprintf_s(buff, " Press 1  : %f \n", jump_time);
				OutputDebugStringA(buff);
			}
			//}
			//else {
			else if (jump_time < 0 && jump_time >((-1)*JUMP_AMOUNT))
			{
				float tempY = jump_time + (g / m_pMass);
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);

				jump_time -= 0.1f;

				char buff[100];
				sprintf_s(buff, " Press 2  : %f \n", jump_time);
				OutputDebugStringA(buff);
			}
			else if (jump_time <= ((-1)*JUMP_AMOUNT))
			{
				JumpIng = false;
				//JumpInputEnd(fTime);
				jump_time = 0.f;
				press_time = 0.f;
				OutputDebugString(TEXT("Press 3 \n"));
			}
			// �ö󰡴ٰ� �����;���  
		//}
		}
		else
		{
			// ������ �ʿ� ����
			float tempY = jump_time + (g / m_pMass);
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * tempY);
			jump_time -= 0.1f;
		}

	}
}
void CPlayer::JumpInputEnd(float fTime)
{
	// ���� End�� Jump�� ���� End�� �ƴ϶� JumpKeyInput�� ���� �󤼤���
	// �׷��ϱ� JumpIng ���⼭ �ʱ�ȭ�ϴ°� �ƴ�
	m_pJumpEnable = true;

	//press_time = 0.f;
	FirstJump = false;
	//jump_time = 0.f;
}

void CPlayer::Up(float fTime)
{
	// �� Mass�� ���� �ȸ��� ���¸� �ٽ� 1�� ������ ��� ��
	m_pMass = 1000.f;
	if (!IsAirMouse)
	{
		//  ���� ���� ���� �ƴϸ� 
		m_pAnimation->ChangeAnimation("KirbyJump");
		m_pAnimation->SetReturnSequenceName("KirbyJump", "KirbyJumpIng");
		IsAirMouse = true;
		m_pMesh->SetRelativeScale(180.f, 180.f, 1.f);
	}
	else
	{
		// �׳� up up up up 

		// �̰� �ٵ� ǳ������ �ؾ� ��

		// y�� ���� �����ؼ� ǳ������ �ϴ°� �ϸ� X�δ� �׳� += ���� �־��ָ� �� 
	}
}

void CPlayer::SpitAir(float fTime)
{
	IsAirMouse = false;
	m_pJumpEnable = false;

	// ���� ��� �ִϸ��̼�
	// !!! ���� ��� �̰� �ƴѵ� �׳� �ᵵ �ɰŰ��� �������ϱ� 
	m_pAnimation->ChangeAnimation("KirbyJumpEnd");
	m_pAnimation->SetReturnSequenceName("KirbyJumpEnd", "KirbyIdle");

	// ���� ���󺹱� 
	m_pMass = 100.f;
	m_pMesh->SetRelativeScale(150.f, 150.f, 1.f);
	// �߰��ؾ� �� �� !
	// ���� ����°� ����Ʈ 

}

void CPlayer::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutputDebugString(TEXT("Block\n"));
}
