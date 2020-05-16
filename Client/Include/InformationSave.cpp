#include "InformationSave.h"
#include <iostream>
#include <fstream>
#include <string>
#include "EngineGlobals.h"


CInformationSave::CInformationSave()
{
	p_SkillType = 0;
	p_HP = 1000;
	p_LifeCount = 3;
}

CInformationSave::~CInformationSave()
{
}

int CInformationSave::GetInformationFromTXT(int & st, float & hp, int & lc)
{
	ifstream fin;

	fin.open("PlayerInfo.txt");

	if (!fin)
	{
		return 0;
	}

	fin >> p_SkillType >> p_HP >> p_LifeCount;
	fin.close();

	st = p_SkillType;
	hp = p_HP;
	lc = p_LifeCount;


	int Result = remove("PlayerInfo.txt");

	if (Result == 0)
	{
		OutputDebugString(TEXT("파일 지워짐 \n"));
	}
	else if (Result == 1)
	{
		OutputDebugString(TEXT("파일 안지워짐 \n"));
	}

	return 1;
}

void CInformationSave::SetInformationToTXT()
{
	ofstream fout;
	fout.open("PlayerInfo.txt");

	fout << p_SkillType << "\t" << p_HP << "\t" << p_LifeCount << endl;

	if (fout.is_open())
		fout.close();
}

void CInformationSave::GetPlayerInformation(int st, float hp, int lc)
{
	p_SkillType = st;
	p_HP = hp;
	p_LifeCount = lc;
}
