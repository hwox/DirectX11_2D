#include "MonsterInfoUI.h"
#include "Component/UIBar.h"
#include "Component/UIImage.h"
#include "EngineGlobals.h"
#include "Component/Text.h"
#include "Input.h"

// 여기서 Monster 이름까지 
CMonsterInfoUI::CMonsterInfoUI()
{
	m_pBar = nullptr;
}
CMonsterInfoUI::~CMonsterInfoUI()
{
	SAFE_RELEASE(m_pBack);
	SAFE_RELEASE(m_pBar);
}

bool CMonsterInfoUI::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pBar = CGameObject::CreateComponent<CUIBar>("MonsterInfo_HPBar");
	m_pBack = CGameObject::CreateComponent<CUIImage>("MonsterInfo_HPBack");

	SetRoot(m_pBack);

	m_pBack->AddChild(m_pBar, TR_POS);

	m_pBack->SetRelativeScale(570.f, 70.f, 1.f);
	m_pBack->SetRelativePos(1350.f, 00.f, 0.f);
	m_pBack->SetZOrder(1);

	m_pBar->SetRelativeScale(570.f, 70.f, 1.f);
	m_pBar->SetRelativePos(0.f, 0.f, 0.f);
	m_pBar->SetZOrder(2);


	m_pBack->SetTexture("MonsterInfo_HPBar", TEXT("UI/MonsterInfo/hp/hp_bar_back.png"));
	m_pBar->SetTexture("MonsterInfo_HPBack", TEXT("UI/MonsterInfo/hp/hp_bar.png"));

	m_fHP = 1000;
	m_fHPMax = 1000;

	return true;
}

void CMonsterInfoUI::Begin()
{
	CGameObject::Begin();
}

void CMonsterInfoUI::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CMonsterInfoUI::Render(float fTime)
{
	CGameObject::Render(fTime);
}
