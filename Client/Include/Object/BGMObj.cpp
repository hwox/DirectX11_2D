#include "BGMObj.h"
#include "Component/Audio.h"

CBGMObj::CBGMObj()	:
	m_pAudio(nullptr)
{
	Stage = 0;
}

CBGMObj::~CBGMObj()
{
	m_pAudio->Stop();
	SAFE_RELEASE(m_pAudio);
}

bool CBGMObj::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");


	SetRoot(m_pAudio);

	return true;
}

void CBGMObj::Begin()
{
	CGameObject::Begin();
}

void CBGMObj::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CBGMObj::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CBGMObj::SetStageBGM(int stage)
{
	Stage = stage;
	switch (Stage)
	{
	case 0:
		m_pAudio->SetSound("TitleBGM", true, "Title\\Title_Bgm.mp3");
		m_pAudio->Play();
		break;
	case 1:
		m_pAudio->SetSound("Stage1BGM", true, "BGM\\bgm_stage_1.mp3");
		m_pAudio->Play();
		break;
	case 2:
		break;
	case 3:
		m_pAudio->SetSound("Stage1BGM", true, "BGM\\bgm_stage_1.mp3");
		m_pAudio->Play();
		break;
	}
}
