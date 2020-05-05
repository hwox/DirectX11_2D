#include "StartMap.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"


CStartMap::CStartMap()
{
	m_pMesh = nullptr;
	m_BackImage = nullptr;
	m_pCamera = nullptr;
	m_pAnimation = nullptr;
}
CStartMap::~CStartMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_BackImage);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pAnimation);
}
bool CStartMap::Init()
{
	if (!CGameObject::Init())
		return false;


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_BackImage = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pCamera = CreateComponent<CCameraComponent>("Camera");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pAnimation->AddAnimation2DSequence("MainTitle");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_BackImage->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TitleAnimMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("StageBackMaterial");

	m_BackImage->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_BackImage);



	m_BackImage->AddChild(m_pCamera, TR_POS);
	m_BackImage->AddChild(m_pMesh, TR_POS);

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(0.f, 0.f, -20.f);
//	m_pCamera->SetCameraPosLimit(StageMinX, StageMaxX, StageMinY, StageMaxY);

//	m_BackImage->AddChild(m_pMesh, TR_POS);

	m_pMesh->SetRelativePos(450.f, 300.f, 0.f);
	m_pMesh->SetRelativeScale(1050.f, 700.f, 1.f);

	m_BackImage->SetRelativePos(0.f, 100.f, 0.f);
	m_BackImage->SetRelativeScale(1920.f,1080.f, 1.f);

	//////////////////////////////////////////////




	return true;
}

void CStartMap::Begin()
{
	CGameObject::Begin();
}

void CStartMap::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CStartMap::Render(float fTime)
{
	CGameObject::Render(fTime);
}
