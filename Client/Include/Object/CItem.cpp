#include "CItem.h"
#include "Resource/Material.h"
#include "Component/ColliderRect.h"
#include "Resource/ResourceManager.h"
#include "EngineGlobals.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Scene/Scene.h"


CItem::CItem()
{
	m_pMovement = nullptr;
	itemMesh = nullptr;
	itemBody = nullptr;
	itemBackMesh = nullptr;
	itemBackAnim = nullptr;
	ItemKind = 0;
}

CItem::~CItem()
{
	SAFE_RELEASE(itemMesh);
	SAFE_RELEASE(itemBody);
	SAFE_RELEASE(itemBackMesh);
	SAFE_RELEASE(itemBackAnim);
	SAFE_RELEASE(m_pMovement);
}

bool CItem::Init()
{
	if (!CGameObject::Init())
		return false;
	itemMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	itemBackMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	itemBody = CreateComponent<CColliderRect>("ItemBody");
	itemBackAnim = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	itemBackAnim->AddAnimation2DSequence("ItemBackEffect");



	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");


	itemBackMesh->SetStaticMesh(pMesh);	
	itemMesh->SetStaticMesh(pMesh);
	itemBackMesh->SetAnimation2D(itemBackAnim);
	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemBackAnimMtrl");

	itemBackMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemMtrl");

	itemMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);
	////

	SetRoot(itemMesh);


	//////////////////////////////////////////////////////////////////

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("ItemMovement");
	m_pMovement->SetUpdateComponent(itemMesh);

	m_pMovement->SetMoveSpeed(10.f);

	//////////////////////////////////////////////////////////////////


	itemMesh->AddChild(itemBody, TR_POS);

	itemBody->SetExtent(50.f, 70.f);
	itemBody->SetPivot(0.5f, 0.5f, 0.f);

	itemBody->SetCollisionProfile("Item");

	itemMesh->AddChild(itemBackMesh, TR_POS);
	itemMesh->SetPivot(0.5f, 0.5f, 0.f);
	itemMesh->SetRelativePos(10.f, 15.f, 0.f);
	itemMesh->SetRelativeScale(45.f, 45.f, 1.f);

	itemBackMesh->SetPivot(0.5f, 0.5f, 0.f);
	itemBackMesh->SetRelativePos(0.f, -5.f, 0.f);
	itemBackMesh->SetRelativeScale(100.f, 100.f, 1.f);

	return true;
}

void CItem::Begin()
{
	CGameObject::Begin();

}

void CItem::Update(float fTime)
{
	CGameObject::Update(fTime);
	WingTime += fTime;

	if ((int)WingTime % 2 == 0)
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * 0.01f);
	}
	else
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * -0.01f);
	}
}

void CItem::Render(float fTime)
{
	CGameObject::Render(fTime);

}

int CItem::GetItemKind()
{
	return ItemKind;
}

void CItem::SetItemKind(int _kind)
{
	ItemKind = _kind;

	switch (_kind)
	{
	case 0:
	{
		GET_SINGLE(CResourceManager)->CreateMaterial("ItemMtrl");

		CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemMtrl");

		pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
		pMaterial->SetTexture(0, "Item", TEXT("Item\\item_0.png"));
		pMaterial->SetRenderState("AlphaBlend");
		pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
		itemMesh->SetMaterial(pMaterial);
		SAFE_RELEASE(pMaterial);
	}
		break;
	case 1:
	{
		GET_SINGLE(CResourceManager)->CreateMaterial("ItemMtrl1");

		CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemMtrl1");

		pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
		pMaterial->SetTexture(0, "Item1", TEXT("Item\\item_1.png"));
		pMaterial->SetRenderState("AlphaBlend");
		pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

		itemMesh->SetMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);
	}
		break;
	case 2:
	{
		GET_SINGLE(CResourceManager)->CreateMaterial("ItemMtrl2");

		CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemMtrl2");

		pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
		pMaterial->SetTexture(0, "Item2", TEXT("Item\\item_2.png"));
		pMaterial->SetRenderState("AlphaBlend");
		pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

		itemMesh->SetMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);
	}
		break;
	case 3:
	{
		GET_SINGLE(CResourceManager)->CreateMaterial("ItemMtrl3");

		CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ItemMtrl3");

		pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
		pMaterial->SetTexture(0, "Item3", TEXT("Item\\item_3.png"));
		pMaterial->SetRenderState("AlphaBlend");
		pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

		itemMesh->SetMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);
	}
		break;
	}
}
