#include "MainGameMode.h"
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
#include "../Object/MainMap.h"
#include "Input.h"
#include "../Object/BGMObj.h"

#include "..\Object\PhoneCallUI.h"
#include "../Object/PlayerHPBar.h"
#include "..\Object\Player.h"
#include "..\Object\PlayerLife.h"
#include "..\Object\MonsterInfoUI.h"

#include "..\Object\WaddleDee.h"

CMainGameMode::CMainGameMode()
{
}

CMainGameMode::~CMainGameMode()
{
}

bool CMainGameMode::Init()
{
	CGameMode::Init();

	GET_SINGLE(CCollisionManager)->CreateChannel("Player", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Monster", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MonsterProjectile", CT_BLOCK);

	GET_SINGLE(CCollisionManager)->CreateProfile("Player", "Player");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Player", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("Monster", "Monster");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Monster", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MonsterProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerProjectile", "PlayerProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "MonsterProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("MonsterProjectile", "MonsterProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MonsterProjectile", CT_IGNORE);

	CreateMaterial();

	CreateAnimation2DSequence();

	CPlayer*	pObj = m_pScene->SpawnObject<CPlayer>();

	SetPlayer(pObj);

	CChildObj*	pChildObj = m_pScene->SpawnObject<CChildObj>("Child");

	pObj->AddChild(pChildObj, TR_ROT | TR_POS);

	SAFE_RELEASE(pChildObj);

	CBGMObj*	pBGMObj = m_pScene->SpawnObject<CBGMObj>("BGMObj");

	pObj->AddChild(pBGMObj, TR_ROT | TR_POS);

	SAFE_RELEASE(pBGMObj);

	SAFE_RELEASE(pObj);


	CWaddleDee*	pMinion2 = m_pScene->SpawnObject<CWaddleDee>(Vector3(1200.f, 130.f, 0.f));

	SAFE_RELEASE(pMinion2);

	CPhoneCallUI*	pPlayerPhone = m_pScene->SpawnObject<CPhoneCallUI>();

	SAFE_RELEASE(pPlayerPhone);

	CPlayerHPBar*	pHPBar = m_pScene->SpawnObject<CPlayerHPBar>();

	SAFE_RELEASE(pHPBar);

	CPlayerLife*	pLifeUI = m_pScene->SpawnObject<CPlayerLife>();

	SAFE_RELEASE(pLifeUI);



	CMonsterInfoUI*	pMonsterLifeUI = m_pScene->SpawnObject<CMonsterInfoUI>();

	SAFE_RELEASE(pMonsterLifeUI);


	CMainMap*	pMap = m_pScene->SpawnObject<CMainMap>();

	SAFE_RELEASE(pMap);



	return true;
}

bool CMainGameMode::CreateMaterial()
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

	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimOutLineMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_OUTLINE_SHADER);
	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->CreateCBufferNode(OUTLINE_CBUFFER, 11, sizeof(OutLineCBuffer));

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("TestPixelMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TestPixelMtrl");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "TestPixel", TEXT("PixelCollision.png"));

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
	pMaterial->AddRef();

	SAFE_RELEASE(pMaterial);

	return true;
}

bool CMainGameMode::CreateAnimation2DSequence()
{
	//GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionIdle", true, 1.f, 7);
	//GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionIdle", "MinionAtlas",
	//	TEXT("Monster/MinionAtlas.png"));

	//for (int i = 0; i < 7; ++i)
	//{
	//	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceFrameInfo("MinionIdle", Vector2(50.f * i, 0.f),
	//		Vector2(50.f * (i + 1), 37.f));
	//}

	//GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionWalk", true, 1.f, 6);

	//for (int i = 0; i <= 5; ++i)
	//{
	//	TCHAR	strFileName[MAX_PATH] = {};

	//	wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-run2-0%d.png"), i);

	//	char	strKey[256] = {};
	//	sprintf_s(strKey, "MinionWalk%d", i);

	//	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionWalk", strKey, strFileName);
	//}

	//GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionWalk", Vector2(0.f, 0.f),
	//	Vector2(50.f, 37.f));

	//GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionKick", false, 1.f, 8);

	//for (int i = 0; i <= 7; ++i)
	//{
	//	TCHAR	strFileName[MAX_PATH] = {};

	//	wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-kick-0%d.png"), i);

	//	char	strKey[256] = {};
	//	sprintf_s(strKey, "MinionKick%d", i);

	//	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionKick", strKey, strFileName);
	//}

	//GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionKick", Vector2(0.f, 0.f),
	//	Vector2(50.f, 37.f));


	Player_Jump_Texture_Create();
	Monster_Texture_Create();

	return true;
}

void CMainGameMode::Player_Jump_Texture_Create()
{
	////////////////////     Kirby Idle      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyIdle", true, 3.f, 18);

	for (int i = 0; i <= 17; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Idle/kirby_idle_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyIdle", Vector2(0.f, 0.f),
		Vector2(20.f, 19.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Walk      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyWalk", true, 1.f, 10);

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Walk/stand_walk_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyWalk%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyWalk", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyWalk", Vector2(0.f, 0.f),
		Vector2(20.f, 19.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Jump      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJump", false, 0.4f, 5);

	for (int i = 0; i <= 4; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Jump/Kirby_Jump_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyJump%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyJump", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyJump", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Jump ING     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJumpIng", true, 1.f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Jump_Ing/Kirby_Jump_Up_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyJumpIng%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyJumpIng", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyJumpIng", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));


	///////////////////////////////////////////////////////////////


	////////////////////     Kirby Jump End     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJumpEnd", false, 0.4f, 5);

	for (int i = 0; i <= 4; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Jump_End/Kirby_Jump_End_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyJumpEnd%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyJumpEnd", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyJumpEnd", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////


	////////////////////     Kirby Down     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDown", false, 1.f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Down/Kirby_Walk_Down_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyDown", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Idle Down     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyIdleDown", false, 1.f, 2);

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Idle_Down/Kirby_Idle_Down_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyIdleDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyIdleDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyIdleDown", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Eat     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyEat", false, 2.f, 15);

	for (int i = 0; i <= 14; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Eat/Kirby_Eat_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyEat%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyEat", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyEat", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby Eat Over     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyEatOver", false, 0.5f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Eat_Over/Kirby_Eat_Over_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyEatOver%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyEatOver", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyEatOver", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

}

void CMainGameMode::Monster_Texture_Create()
{

	////////////////////    Monster Idle      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WaddleDeeIdle", true, 1.f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/WaddleDee_Idle/WaddleDee_Idle_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "WaddleDeeIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WaddleDeeIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WaddleDeeIdle", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Monster Damage      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WaddleDeeDamage", true, 1.f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/WaddleDee_Damage/WaddleDee_Damage_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "WaddleDeeDamage%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WaddleDeeDamage", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WaddleDeeDamage", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Monster Move      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WaddleDeeMove", true, 1.f, 8);

	for (int i = 0; i <= 7; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/WaddleDee_Move/WaddleDee_Move_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "WaddleDeeMove%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WaddleDeeMove", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WaddleDeeMove", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////
}

