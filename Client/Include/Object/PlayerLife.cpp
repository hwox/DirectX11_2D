#include "PlayerLife.h"
#include "Component/UIImage.h"
#include "EngineGlobals.h"
#include "..\Object\PlayerHpBar.h"

CPlayerLife::CPlayerLife()
{
	m_Image = nullptr;
	m_ImageX = nullptr;
	m_NumberCount = nullptr;
	m_NumberCount_zero = nullptr;
	m_pHPBar = nullptr;
	u_pSkillTypeImage = nullptr;
	m_pHP = MAX_HP;
}

CPlayerLife::~CPlayerLife()
{
	SAFE_RELEASE(m_pHPBar);
	SAFE_RELEASE(m_ImageX);
	SAFE_RELEASE(m_NumberCount_zero);
	SAFE_RELEASE(m_NumberCount);
	SAFE_RELEASE(m_Image);
	SAFE_RELEASE(u_pSkillTypeImage);
}

bool CPlayerLife::Init()
{
	if (!CGameObject::Init())
		return false;



	m_Image = CGameObject::CreateComponent<CUIImage>("PlayerInfo_UIImage");
	m_NumberCount = CGameObject::CreateComponent<CUIImage>("PlayerInfo_NumberCount");
	m_ImageX = CGameObject::CreateComponent<CUIImage>("PlayerInfo_UIImageX");
	m_NumberCount_zero = CGameObject::CreateComponent<CUIImage>("PlayerInfo_NumberCount_zero");
	u_pSkillTypeImage = CGameObject::CreateComponent<CUIImage>("SkillTypeImage");


	m_pHPBar = m_pScene->SpawnObject<CPlayerHpBar>();
	//SAFE_RELEASE(m_pHPBar);
	// ¾êµµ 

	SetRoot(m_ImageX);

	//m_ImageX->AddChild(m_pHPBar, TR_POS);

	m_ImageX->AddChild(m_Image, TR_POS);
	m_ImageX->AddChild(m_NumberCount, TR_POS);
	m_ImageX->AddChild(m_NumberCount_zero, TR_POS);
	m_ImageX->AddChild(u_pSkillTypeImage, TR_POS);

	m_ImageX->SetRelativeScale(40.f, 30.f, 1.f);
	m_ImageX->SetRelativePos(600.f, 30.f, 1.f);
	m_ImageX->SetZOrder(1);


	m_Image->SetRelativeScale(80.f, 80.f, 1.f);
	m_Image->SetRelativePos(-85.f, -10.f, 0.f);
	m_Image->SetZOrder(2);

	m_NumberCount_zero->SetRelativeScale(60.f, 60.f, 1.f);
	m_NumberCount_zero->SetRelativePos(50.f, -10.f, 0.f);
	m_NumberCount_zero->SetZOrder(2);

	m_NumberCount->SetRelativeScale(60.f, 60.f, 1.f);
	m_NumberCount->SetRelativePos(115.f, -10.f, 0.f);
	m_NumberCount->SetZOrder(2);

	u_pSkillTypeImage->SetRelativeScale(200.f, 50.f, 1.f);
	u_pSkillTypeImage->SetRelativePos(-550.f, 0.f, 0.f);
	u_pSkillTypeImage->SetZOrder(2);


	m_ImageX->SetTexture("PlayerInfo_UIImageX", TEXT("UI/PlayerInfo/life/kirby_life_ui.png"));
	m_NumberCount->SetTexture("PlayerInfo_NumberCount3", TEXT("UI/PlayerInfo/life/kirby_life_ui_count/kirby_life_ui_count_3.png"));
	m_NumberCount_zero->SetTexture("PlayerInfo_NumberCount0", TEXT("UI/PlayerInfo/life/kirby_life_ui_count/kirby_life_ui_count_0.png"));
	m_Image->SetTexture("PlayerInfo_UIImage", TEXT("UI/PlayerInfo/life/kirby_life_ui_image/kirby_life_ui_image_0.png"));

	u_pSkillTypeImage->SetTexture("SkillTypeImage_Normal", TEXT("UI/SkillType/Skill_Title_Normal.png"));

	lifeCount = 3;
	KirbyState = 0;

	return true;
}

void CPlayerLife::Begin()
{
	CGameObject::Begin();
}

void CPlayerLife::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (m_pHP < 0)
	{
		SetLifeCount(lifeCount--);
	}
	m_pHPBar->SetPercentHPBar(m_pHP / MAX_HP);

}

void CPlayerLife::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CPlayerLife::SetLifeCount(int count)
{
	lifeCount = count;
	TCHAR	strTempImagePath[MAX_PATH] = {};
	wsprintf(strTempImagePath, TEXT("UI/PlayerInfo/life/kirby_life_ui_count/kirby_life_ui_count_%d.png"), count);


	char	strKey[256] = {};
	sprintf_s(strKey, "PlayerInfo_NumberCount%d", count);

	m_NumberCount->SetTexture(strKey, strTempImagePath);
}

void CPlayerLife::SetKirbyState(int state)
{
	//TCHAR	strTempImagePath[MAX_PATH] = {};
	//wsprintf(strTempImagePath, strImageFileName);

	//wcscat_s(strImageFileName, TEXT("%d.png", state - 1));

	//m_Image->SetTexture("PlayerInfo_UIImage", strImageFileName);
}

void CPlayerLife::SetHP(float hp)
{
	m_pHP = hp;
}

float CPlayerLife::GetHP()
{
	return m_pHP;
}

void CPlayerLife::SetSkillTitle_Normal()
{
	KirbyState = 0;
	u_pSkillTypeImage->SetTexture("SkillTypeImage_Normal", TEXT("UI/SkillType/Skill_Title_Normal.png"));
}

void CPlayerLife::SetSkillTitle_Beam()
{
	KirbyState = 1;
	u_pSkillTypeImage->SetTexture("SkillTypeImage_Beam", TEXT("UI/SkillType/Skill_Title_Beam.png"));
}

void CPlayerLife::SetSkillTitle_Cutter()
{
	KirbyState = 2;
	u_pSkillTypeImage->SetTexture("SkillTypeImage_Cutter", TEXT("UI/SkillType/Skill_Title_Cutter.png"));
}

void CPlayerLife::SetSkillTitle(int KirbyState)
{
	switch (KirbyState)
	{
	case 0:
		SetSkillTitle_Normal();
		break;
	case 1:
		SetSkillTitle_Beam();
		break;
	case 2:
		SetSkillTitle_Cutter();
		break;
	}

}
