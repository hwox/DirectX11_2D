#include "Stage1Mode.h"
#include "../Object/TestObject.h"
#include "../Object/Minion.h"
#include "../Object/ChildObj.h"
#include "Scene/Scene.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Resource/Animation2DSequence.h"
#include "CollisionManager.h"
#include "../Object/TestPixelCollision.h"
#include "../Object/TestButton.h"
#include "../Object/TestBar.h"
#include "../Object/Stage1Map.h"
#include "Input.h"
#include "../Object/BGMObj.h"

#include "..\Object\PhoneCallUI.h"
#include "../Object/PlayerHPBar.h"
#include "..\Object\Player.h"
#include "..\Object\PlayerLife.h"

#include "..\Object\WaddleDee.h"
#include "../Object/Title.h"
#include "..\Object\Leap.h"

#define STAGE1_MINX		0
#define STAGE1_MAXX		9500
#define STAGE1_MINY		50
#define STAGE1_MAXY		800

CStage1Mode::CStage1Mode()
{
}

CStage1Mode::~CStage1Mode()
{
}

bool CStage1Mode::Init()
{
	CGameMode::Init();


	SetCollidrProfile();


	CStage1Map*	pMap = m_pScene->SpawnObject<CStage1Map>();
	pMap->SetStageSize(STAGE1_MINX, STAGE1_MAXX, STAGE1_MINY, STAGE1_MAXY);
	SAFE_RELEASE(pMap);


	CPlayer*	pObj = m_pScene->SpawnObject<CPlayer>();
	pObj->SetStageMinMax(STAGE1_MINX, STAGE1_MAXX, STAGE1_MINY, STAGE1_MAXY);
	SetPlayer(pObj);

	//CBGMObj*	pBGMObj = m_pScene->SpawnObject<CBGMObj>("BGMObj");

	//pObj->AddChild(pBGMObj, TR_ROT | TR_POS);

	//SAFE_RELEASE(pBGMObj);

	SAFE_RELEASE(pObj);


	CTitle*	pTitle = m_pScene->SpawnObject<CTitle>();

	SAFE_RELEASE(pTitle);

	CPhoneCallUI*	pPlayerPhone = m_pScene->SpawnObject<CPhoneCallUI>();

	SAFE_RELEASE(pPlayerPhone);

	SpawnMonster();


	return true;
}

void CStage1Mode::SpawnMonster()
{

	CWaddleDee*	pMinion = m_pScene->SpawnObject<CWaddleDee>(Vector3(3900.f, 230.f, 0.f));

	SAFE_RELEASE(pMinion);


	CWaddleDee*	pMinion2 = m_pScene->SpawnObject<CWaddleDee>(Vector3(2500.f, 230.f, 0.f));

	SAFE_RELEASE(pMinion2);


	CLeap*	pLeap = m_pScene->SpawnObject<CLeap>(Vector3(6300.f, 500.f, 0.f));
	SAFE_RELEASE(pLeap);
}

void CStage1Mode::SetCollidrProfile()
{
	GET_SINGLE(CCollisionManager)->CreateChannel("Player", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerMap", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Monster", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MonsterProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Map", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MapObject", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("SceneChange", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MapBlock", CT_BLOCK);




	GET_SINGLE(CCollisionManager)->CreateProfile("Player", "Player");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Player", CT_IGNORE);
	//	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerMap", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "MapObject", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("Monster", "Monster");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Monster", CT_IGNORE);
	//	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "PlayerMap", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MapBlock", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerProjectile", "PlayerProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerMap", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "SceneChange", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("MonsterProjectile", "MonsterProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerMap", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MapBlock", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("Map", "Map");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "MapObject", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "MapBlock", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("MapObject", "MapObject");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "MapObject", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "MapBlock", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Map", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("MapBlock", "MapBlock");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapBlock", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapBlock", "MapObject", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapBlock", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapBlock", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapBlock", "MonsterProjectile", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Map", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerMap", "PlayerMap");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "SceneChange", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("SceneChange", "SceneChange");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "PlayerMap", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "SceneChange", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("SceneChange", "MapBlock", CT_IGNORE);

}
