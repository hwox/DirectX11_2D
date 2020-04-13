#include "BGMObj.h"
#include "Component/Audio.h"

CBGMObj::CBGMObj()	:
	m_pAudio(nullptr)
{
}

CBGMObj::~CBGMObj()
{
	SAFE_RELEASE(m_pAudio);
}

bool CBGMObj::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");

	m_pAudio->SetSound("Stage1BGM", true, "Bgm/Stage/bgm_stage_1.mp3");
	m_pAudio->Play();

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
