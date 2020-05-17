#include "MagicMirror.h"
#include "EngineGlobals.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"

#include "Component/ColliderRect.h"
#include "Stage2Map.h"
#include "..\GameMode\Stage2Mode.h"
#include "..\GameMode\Stage1Mode.h"
#include "..\GameMode\Stage3Mode.h"

#include "..\Object\Player.h"
#include "..\InformationSave.h"

CMagicMirror::CMagicMirror()
{
	m_pMesh = nullptr;
	m_pAnimation = nullptr;
	m_pBody = nullptr;
	m_pInfo = nullptr;
	m_pPlayer = nullptr;
}

CMagicMirror::~CMagicMirror()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pInfo);
	SAFE_RELEASE(m_pPlayer);
}

bool CMagicMirror::Init()
{
	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("MirrorBody");

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pAnimation->AddAnimation2DSequence("MagicMirror");
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);
	SetRoot(m_pMesh);

//	m_pMesh->SetRelativePos(7500.f, 400.f, 0.f);
	m_pMesh->SetRelativeScale(250.f, 320.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.f, 0.f);

	m_pBody->SetExtent(50.f, 250.f);
	m_pBody->SetPivot(0.5f, 0.f, 0.f);
	m_pBody->SetCollisionProfile("SceneChange");
	m_pBody->AddBlockCallback<CMagicMirror>(this, &CMagicMirror::OnBlock);

	
	return true;
}

void CMagicMirror::Begin()
{
	CGameObject::Begin();

	m_pPlayer = (CPlayer*)m_pScene->GetGameMode()->GetPlayer();
}

void CMagicMirror::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CMagicMirror::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CMagicMirror::SetStageMode(int Mode)
{
	StageMode = Mode;
}

int CMagicMirror::GetStageMode()
{
	return StageMode;
}

void CMagicMirror::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	m_pPlayer->SetPlayerInfo();


	switch (StageMode)
	{
	case 1:
	{
		CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();

		pNextScene->SetGameMode<CStage3Mode>();

		//CPlayer* temp = (CPlayer*)m_pScene->GetGameMode()->GetPlayer();
		//temp->SetPlayerInfo();
		//SAFE_RELEASE(temp);
	}
		break;
	case 2:



		break;
	case 3:
		break;
	}
}

