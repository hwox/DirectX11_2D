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


#define STAGE1_MINX		0
#define STAGE1_MAXX		10000
#define STAGE1_MINY		0
#define STAGE1_MAXY		1200

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

	SAFE_RELEASE(pMap);


	CPlayer*	pObj = m_pScene->SpawnObject<CPlayer>();
	pObj->SetStageMinMax(0, 10000.f, 50.f, 300.f);
	SetPlayer(pObj);

	//CBGMObj*	pBGMObj = m_pScene->SpawnObject<CBGMObj>("BGMObj");

	//pObj->AddChild(pBGMObj, TR_ROT | TR_POS);

	//SAFE_RELEASE(pBGMObj);

	SAFE_RELEASE(pObj);


	CPhoneCallUI*	pPlayerPhone = m_pScene->SpawnObject<CPhoneCallUI>();

	SAFE_RELEASE(pPlayerPhone);

	SpawnMonster();


	return true;
}

void CStage1Mode::SpawnMonster()
{

	CWaddleDee*	pMinion = m_pScene->SpawnObject<CWaddleDee>(Vector3(1800.f, 250.f, 0.f));

	SAFE_RELEASE(pMinion);

}

void CStage1Mode::SetCollidrProfile()
{
	GET_SINGLE(CCollisionManager)->CreateChannel("Player", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerMap", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Monster", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MonsterProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerAirZone", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Map", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MapObject", CT_BLOCK);

	GET_SINGLE(CCollisionManager)->CreateProfile("Player", "Player");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Player", CT_IGNORE);
	//	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerMap", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("Monster", "Monster");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Monster", CT_IGNORE);
	//	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "PlayerMap", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerProjectile", "PlayerProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerMap", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("MonsterProjectile", "MonsterProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerMap", CT_IGNORE);




	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerAirZone", "PlayerAirZone");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "PlayerMap", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerAirZone", "MapObject", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateProfile("Map", "Map");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "PlayerAirZone", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Map", "MapObject", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("MapObject", "MapObject");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "Map", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MapObject", "PlayerAirZone", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerMap", "PlayerMap");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "PlayerAirZone", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerMap", "Monster", CT_IGNORE);
}
