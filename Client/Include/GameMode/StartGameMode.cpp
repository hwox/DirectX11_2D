#include "StartGameMode.h"
#include "../Object/StartButton.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation2DSequence.h"
#include "Resource/Material.h"
#include "../Object/Title.h"
#include "..\Object\StartMap.h"
#include "../Object/BGMObj.h"

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
	SetPlayer(pMap);
	SAFE_RELEASE(pMap);

	CStartButton*	pStartButton = m_pScene->SpawnObject<CStartButton>();
	pStartButton->SetT(1);
	SAFE_RELEASE(pStartButton);

	CBGMObj*	pBGMObj = m_pScene->SpawnObject<CBGMObj>("BGMObj");
	pBGMObj->SetStageBGM(0);
	SAFE_RELEASE(pBGMObj);

	return true;
}

void CStartGameMode::CreateAnimation2DSequence()
{
	Player_Stand_Texture_Create();
	Player_Skill_Beam_Texture_Create();
	Player_Skill_Cutter_Texture_Create();
	Monster_Texture_Create();
	Effect_Texture_Create();
	Else_Texture_Create();
}

void CStartGameMode::Player_Stand_Texture_Create()
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

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbySplitStar", false, 1.2f, 14);

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

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDigestMonster", false, 0.9f, 8);

	for (int i = 0; i <= 7; ++i)
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

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyDigest", false, 0.8f, 6);

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

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyJumpDown", false, 0.7f, 9);

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


		////////////////////     Kirby MonsterWlak   ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyMonsterWalk", true, 0.7f, 14);

	for (int i = 0; i <= 13; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_MonsterWalk/Kirby_MonsterWalk_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyMonsterWalk%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyMonsterWalk", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyMonsterWalk", Vector2(0.f, 0.f),
		Vector2(27.f, 27.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby MonsterJump   ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyMonsterJump", true, 0.7f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_MonsterJump/Kirby_MonsterJump_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyMonsterJump%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyMonsterJump", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyMonsterJump", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby MonsterJumpUp   ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyMonsterJumpUp", true, 0.7f, 1);

	for (int i = 0; i <= 0; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/monster_jump_up.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyMonsterJumpUp%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyMonsterJumpUp", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyMonsterJumpUp", Vector2(0.f, 0.f),
		Vector2(30.f, 35.f));

	///////////////////////////////////////////////////////////////

	////////////////////     Kirby MonsterIdle  ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("KirbyMonsterIdle", true, 0.7f, 9);

	for (int i = 0; i <= 8; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Kirby_MonsterIdle/Kirby_MonsterIdle_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "KirbyMonsterIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("KirbyMonsterIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("KirbyMonsterIdle", Vector2(0.f, 0.f),
		Vector2(27.f, 25.f));

	///////////////////////////////////////////////////////////////
}

void CStartGameMode::Player_Skill_Beam_Texture_Create()
{

	////////////////////    Beam Idle      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamIdle", true, 1.5f, 9);

	for (int i = 0; i <= 8; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_Idle/Beam_Idle_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamIdle", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////


	////////////////////    Beam IdleDown      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamIdleDown", true, 0.5f, 2);

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_IdleDown/Beam_IdleDown_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamIdleDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamIdleDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamIdleDown", Vector2(0.f, 0.f),
		Vector2(26.f, 25.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Beam Jump Down      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamJumpDown", false, 1.0f, 10);

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_JumpDown/Beam_JumpDown_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamJumpDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamJumpDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamJumpDown", Vector2(0.f, 0.f),
		Vector2(27.f, 35.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Beam Walk      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamWalk", true, 1.2f, 12);

	for (int i = 0; i <= 11; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_Walk/Beam_Walk_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamWalk%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamWalk", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamWalk", Vector2(0.f, 0.f),
		Vector2(30.f, 25.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Beam Jump UP     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamJumpUp", true, 1.0f, 1);

	for (int i = 0; i <= 0; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/beam_jump_up.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamJumpUp%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamJumpUp", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamJumpUp", Vector2(0.f, 0.f),
		Vector2(25.f, 26.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Beam Damage     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamDamage", false, 1.5f, 15);

	for (int i = 0; i <= 14; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_Damage/Beam_Damage_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamDamage%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamDamage", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamDamage", Vector2(0.f, 0.f),
		Vector2(27.f, 36.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Beam Jump Ing     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamJumpIng", true, 0.8f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Bean_Jump_Ing/Beam_Jump_Ing_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamJumpIng%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamJumpIng", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamJumpIng", Vector2(0.f, 0.f),
		Vector2(30.f, 35.f));

	///////////////////////////////////////////////////////////////


			////////////////////    Beam Jump End    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamJumpEnd", false, 0.8f, 5);

	for (int i = 0; i <= 4; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_Jump_End/Beam_Jump_End_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamJumpEnd%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamJumpEnd", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamJumpEnd", Vector2(0.f, 0.f),
		Vector2(30.f, 35.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Beam Attack    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamAttack", false, 3.0f, 35);

	for (int i = 0; i <= 34; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_Attack/Beam_Attack_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamAttack%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamAttack", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamAttack", Vector2(0.f, 0.f),
		Vector2(75.f, 90.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Beam SplitAir    ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BeamSplitAir", false, 0.8f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Beam/Beam_SplitAir/Beam_SplitAir_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "BeamSplitAir%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BeamSplitAir", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BeamSplitAir", Vector2(0.f, 0.f),
		Vector2(25.f, 30.f));

	///////////////////////////////////////////////////////////////

}

void CStartGameMode::Player_Skill_Cutter_Texture_Create()
{



		////////////////////    Cutter Attack      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterAttack", false, 0.8f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Attack/Cutter_Attack_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterAttack%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterAttack", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterAttack", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////

			////////////////////    Cutter Bullet      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterBullet", true, 0.6f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Bullet/Cutter_Bullet_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterBullet%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterBullet", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterBullet", Vector2(0.f, 0.f),
		Vector2(31.f, 22.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Cutter Digestion      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterDigestion", false, 0.6f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Digestion/Cutter_Digestion_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterDigestion%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterDigestion", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterDigestion", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Cutter jump Down      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterJumpDown", false, 0.6f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Jump_Down/Cutter_Jump_Down_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterJumpDown%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterJumpDown", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterJumpDown", Vector2(0.f, 0.f),
		Vector2(25.f, 27.f));

	///////////////////////////////////////////////////////////////

	////////////////////    Cutter Walk      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterWalk", false, 1.f, 10);

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Walk/Cutter_Walk_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterWalk%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterWalk", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterWalk", Vector2(0.f, 0.f),
		Vector2(25.f, 27.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Cutter SplitAir      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterSplitAir", false, 1.f, 3);

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_SplitAir/Cutter_SplitAir_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterSplitAir%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterSplitAir", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterSplitAir", Vector2(0.f, 0.f),
		Vector2(30.f, 30.f));

	///////////////////////////////////////////////////////////////

			////////////////////    Cutter JumpIng      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterJumpIng", true, 1.f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Jump_Ing/Cutter_Jump_Ing_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterJumpIng%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterJumpIng", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterJumpIng", Vector2(0.f, 0.f),
		Vector2(30.f, 35.f));

	///////////////////////////////////////////////////////////////

		////////////////////    Cutter Jump Up      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterJumpUp", false, 1.f, 1);

	for (int i = 0; i <= 0; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_jump_up.png"));

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterJumpUp%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterJumpUp", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterJumpUp", Vector2(0.f, 0.f),
		Vector2(25.f, 30.f));

	///////////////////////////////////////////////////////////////

			////////////////////    Cutter Idle      ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CutterIdle", false, 1.f, 1);

	for (int i = 0; i <= 0; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Skill/Cutter/Cutter_Idle/Cutter_Idle_0.png"));

		char	strKey[256] = {};
		sprintf_s(strKey, "CutterIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CutterIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CutterIdle", Vector2(0.f, 0.f),
		Vector2(25.f, 25.f));

	///////////////////////////////////////////////////////////////
}

void CStartGameMode::Monster_Texture_Create()
{

	////////////////////    WaddleDee Idle      ///////////////////////

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

	////////////////////    WaddleDee Damage      ///////////////////////

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

		////////////////////    WaddleDee Move      ///////////////////////

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




	////////////////////   Leap Idle(Move)     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LeapIdle", true, 0.5f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/Leap_Idle/Leap_Idle_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "LeapIdle%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LeapIdle", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LeapIdle", Vector2(0.f, 0.f),
		Vector2(27.f, 20.f));

	///////////////////////////////////////////////////////////////


	////////////////////   Leap Attack     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LeapAttack", true, 0.5f, 2);

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/Leap_Attack/Leap_Attack_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "LeapAttack%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LeapAttack", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LeapAttack", Vector2(0.f, 0.f),
		Vector2(23.f, 20.f));

	///////////////////////////////////////////////////////////////


	////////////////////   Leap Damage     ///////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LeapDamage", true, 0.5f, 2);

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/Leap_Attack/Leap_Attack_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "LeapDamage%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LeapDamage", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LeapDamage", Vector2(0.f, 0.f),
		Vector2(29.f, 27.f));

	///////////////////////////////////////////////////////////////
}

void CStartGameMode::Effect_Texture_Create()
{
	////////////////////////////     Star Bullet    ///////////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("StarBullet", true, 0.7f, 4);

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

	///////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("PlayerBullet", true, 0.5f, 4);
	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("PlayerBullet", "KirbyAtlas_PlayerBullet",
		TEXT("attack_star.png"));

	for (int i = 0; i < 4; ++i)
	{
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceFrameInfo("PlayerBullet", Vector2(27.f * i, 0.f),
			Vector2(27.f * (i + 1), 27.f));
	}

	////////////////////////////     Star Bullet Effect   ///////////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("StarBulletEffect", false, 0.2f, 5);

	for (int i = 0; i <= 4; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/StarBullet/BulletEffect/BulletEffect_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "StarBulletEffect%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("StarBulletEffect", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("StarBulletEffect", Vector2(0.f, 0.f),
		Vector2(16.f, 16.f));

	///////////////////////////////////////////////////////////////////////////////


	////////////////////////////     Jump Effect   ///////////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JumpEffect", false, 0.3f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Effect/Jump_Effect/Jump_Effect_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "JumpEffect%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JumpEffect", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JumpEffect", Vector2(0.f, 0.f),
		Vector2(10.f, 10.f));

	///////////////////////////////////////////////////////////////////////////

	////////////////////////////     Split Effect   ///////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SplitAirEffect", false, 0.4f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Effect/SplitAir_Effect/SplitAir_Effect_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "SplitAirEffect%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SplitAirEffect", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SplitAirEffect", Vector2(0.f, 0.f),
		Vector2(20.f, 20.f));

	///////////////////////////////////////////////////////////////////////////


	//////////////////////    Leap Bullet Effect   ///////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LeapAttackEffect", true, 0.4f, 2);

	for (int i = 1; i <= 2; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Player/Effect/Leap_AttackEffect/Leap_AttackEffect_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "LeapAttackEffect%d", i - 1);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LeapAttackEffect", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LeapAttackEffect", Vector2(0.f, 0.f),
		Vector2(16.f, 11.f));

	///////////////////////////////////////////////////////////////////////////


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


	////////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MagicMirror", true, 1.0f, 4);

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Obstacle/MagicMirror/MagicMirror_%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MagicMirror%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MagicMirror", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MagicMirror", Vector2(0.f, 0.f),
		Vector2(60.f, 50.f));
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

	GET_SINGLE(CResourceManager)->CreateMaterial("TitleAnimMtrl");

	 pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TitleAnimMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
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
