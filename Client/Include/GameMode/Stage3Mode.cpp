#include "Stage3Mode.h"
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
#include "../Object/Stage3Map.h"
#include "Input.h"
#include "../Object/BGMObj.h"

#include "..\Object\PhoneCallUI.h"
#include "../Object/PlayerHPBar.h"
#include "..\Object\Player.h"
#include "..\Object\PlayerLife.h"

#include "..\Object\WaddleDee.h"
#include "../Object/Title.h"
#include "..\Object\Leap.h"
#include "..\Object\MapBlock.h"


#define STAGE1_MINX		0
#define STAGE1_MAXX		9500
#define STAGE1_MINY		50
#define STAGE1_MAXY		800

CStage3Mode::CStage3Mode()
{
}

CStage3Mode::~CStage3Mode()
{

}

bool CStage3Mode::Init()
{
	CGameMode::Init();


	CreateMaterial();

	SetCollidrProfile();


	CStage3Map*	pMap = m_pScene->SpawnObject<CStage3Map>();
	pMap->SetStageSize(STAGE1_MINX, STAGE1_MAXX, STAGE1_MINY, STAGE1_MAXY);
	SAFE_RELEASE(pMap);


	CPlayer*	pObj = m_pScene->SpawnObject<CPlayer>(Vector3(800.f, 600.f, 0.f));
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


	//SpawnMonster();


	return true;
}

void CStage3Mode::SpawnMonster()
{

	CWaddleDee*	pMinion = m_pScene->SpawnObject<CWaddleDee>(Vector3(3900.f, 230.f, 0.f));

	SAFE_RELEASE(pMinion);


	CWaddleDee*	pMinion2 = m_pScene->SpawnObject<CWaddleDee>(Vector3(2500.f, 230.f, 0.f));

	SAFE_RELEASE(pMinion2);


	CLeap*	pLeap = m_pScene->SpawnObject<CLeap>(Vector3(6300.f, 500.f, 0.f));
	SAFE_RELEASE(pLeap);


	//CMapBlock*	block = m_pScene->SpawnObject<CMapBlock>(Vector3(1700.f, 400.f, 0.f));
	////m_MapObstacleList.push_back(block);
	//SAFE_RELEASE(block);


}

void CStage3Mode::SetCollidrProfile()
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

bool CStage3Mode::CreateMaterial()
{
	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerMtrl");

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("MonsterAnimMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MonsterAnimMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimOutLineMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_OUTLINE_SHADER);
	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->CreateCBufferNode(OUTLINE_CBUFFER, 11, sizeof(OutLineCBuffer));

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapTileMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapTileMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "MainMapTile", TEXT("Tile.bmp"));

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapIsoTileMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapIsoTileMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);

	vector<const TCHAR*>	vecPath;

	for (int i = 0; i <= TILE_COUNT; ++i)
	{
		TCHAR* pPath = new TCHAR[MAX_PATH];

		wsprintf(pPath, TEXT("Map\\Tile_Test_%d.png"), i);

		vecPath.push_back(pPath);
	}

	pMaterial->SetTexture(10, "MainMapIsoTile", vecPath);
	pMaterial->SetRenderState(RENDERSTATE_ALPHABLEND);

	for (size_t i = 0; i < vecPath.size(); ++i)
	{
		SAFE_DELETE_ARRAY(vecPath[i]);
	}

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BulletMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "Bullet", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->EnableInstancing();
	//pMaterial->AddRef();

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BulletAnimMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletAnimMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->AddRef();
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("StageBackMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("StageBackMaterial");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "StageBG", TEXT("stagebackground.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1Material");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1Material");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1BG", TEXT("stage_1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2Material");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2Material");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2BG", TEXT("stage_2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3Material");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3Material");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3BG", TEXT("stage_3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("ObstacleMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ObstacleMaterial");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Obstacle", TEXT("Tile_Test_0.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

	SAFE_RELEASE(pMaterial);



	return true;
}
