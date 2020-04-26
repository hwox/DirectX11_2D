#include "StartGameMode.h"
#include "../Object/StartButton.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation2DSequence.h"
#include "Resource/Material.h"
#include "../Object/Title.h"
#include "..\Object\StartMap.h"


CStartGameMode::CStartGameMode()
{
}

CStartGameMode::~CStartGameMode()
{
}

bool CStartGameMode::Init()
{
	CGameMode::Init();

	//CTitle*	pTitle = m_pScene->SpawnObject<CTitle>();

	//SAFE_RELEASE(pTitle);

	//GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MouseDefault", true, 1.f, 13);

	CreateMaterial();
	CreateAnimation2DSequence();

	CStartMap*	pMap = m_pScene->SpawnObject<CStartMap>();

	SAFE_RELEASE(pMap);

	//for (int i = 0; i <= 12; ++i)
	/*{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Mouse/Default/%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MouseDefault%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MouseDefault", strKey, strFileName);
	}
*/
//GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MouseDefault", Vector2(0.f, 0.f),
	//Vector2(32.f, 31.f));

//GET_SINGLE(CInput)->CreateAnim2D();
//GET_SINGLE(CInput)->AddAnim2DSequence("MouseDefault");
//GET_SINGLE(CInput)->AlphaBlendEnable();

	CStartButton*	pStartButton = m_pScene->SpawnObject<CStartButton>();

	SAFE_RELEASE(pStartButton);



	return true;
}

void CStartGameMode::CreateAnimation2DSequence()
{
	Player_Jump_Texture_Create();
	Monster_Texture_Create();
	Effect_Texture_Create();
	Else_Texture_Create();
}

void CStartGameMode::Player_Jump_Texture_Create()
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

	////////////////////     Kirby Damage     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDamage", false, 0.8f, 9);

	for (int i = 0; i <= 8; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Damage/Kirby_Damage_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyDamage%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyDamage", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyDamage", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

		////////////////////     Kirby SplitStar     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbySplitStar", false, 1.0f, 14);

	for (int i = 0; i <= 13; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_SplitStar/Kirby_SplitStar_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbySplitStar%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbySplitStar", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbySplitStar", Vector2(0.f, 0.f),
		Vector2(65.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby DigestMonster     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDigestMonster", false, 1.0f, 14);

	for (int i = 0; i <= 13; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_DigestMonster/Kirby_DigestMonster_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyDigestMonster%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyDigestMonster", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyDigestMonster", Vector2(0.f, 0.f),
		Vector2(60.f, 30.f));

	///////////////////////////////////////////////////////////////


	////////////////////     Kirby Digest    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDigest", false, 1.0f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_Digestion/Kirby_Digestion_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyDigest%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyDigest", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyDigest", Vector2(0.f, 0.f),
		Vector2(60.f, 30.f));

	///////////////////////////////////////////////////////////////


		////////////////////     Kirby Jump Up    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJumpUp", true, 1.0f, 1);

	for (int i = 0; i < 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/jump_up.png"));

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyJumpUp%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyJumpUp", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyJumpUp", Vector2(0.f, 0.f),
		Vector2(20.f, 20.f));

	///////////////////////////////////////////////////////////////


	////////////////////     Kirby Jump Down    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJumpDown", false, 1.0f, 9);

	for (int i = 0; i <= 8; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Jump_Down/Jump_Down_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyJumpDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyJumpDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyJumpDown", Vector2(0.f, 0.f),
		Vector2(25.f, 20.f));

	///////////////////////////////////////////////////////////////
}

void CStartGameMode::Monster_Texture_Create()
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

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WaddleDeeDamage", true, 0.3f, 2);

	for (int i = 0; i <= 1; ++i)
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

			////////////////////    WaddleDee Blackhole     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WaddleDeeBlackhole", true, 0.2f, 2);

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/WaddleDee_Blackhole/WaddleDee_Blackhole_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "WaddleDeeBlackhole%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WaddleDeeBlackhole", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WaddleDeeBlackhole", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////
}

void CStartGameMode::Effect_Texture_Create()
{
	////////////////////     Star Bullet    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("StarBullet", true, 1.0f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/StarBullet/StarBullet_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "StarBullet%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("StarBullet", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("StarBullet", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////

}

void CStartGameMode::Else_Texture_Create()
{
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MainTitle", true, 1.0f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("MainTitle/Kirby_Title/Kirby_Title_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MainTitle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MainTitle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MainTitle", Vector2(0.f, 0.f),
		Vector2(190.f, 30.f));
}

bool CStartGameMode::CreateMaterial()
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
	//pMaterial->AddRef();

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



	return true;
}
