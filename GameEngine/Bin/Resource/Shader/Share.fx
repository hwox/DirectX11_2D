
cbuffer Transform	: register(b0)
{
	matrix	g_matWorld;
	matrix	g_matView;
	matrix	g_matProj;
	matrix	g_matWV;
	matrix	g_matWVP;
	float3	g_vMeshPivot;
	float	g_fTrEmpty;
	float3	g_vMeshSize;
	float	g_fTrEmpty1;
};

cbuffer	Material	: register(b1)
{
	float4	g_vMtrlDif;
}

Texture2D	g_BaseTexture : register(t0);

SamplerState	g_LinearSmp	: register(s0);

//SamplerState	g_LinearSmp
//{
//	Filter = MIN_MAG_MIP_LINEAR;
//	AddressU = Wrap;
//	AddressV = Wrap;
//};

static const float2	g_vNullPos[4]	=
{
	float2(-1.f, 1.f),
	float2(1.f, 1.f),
	float2(-1.f, -1.f),
	float2(1.f, -1.f)
};

static const float2	g_vNullUV[4]	=
{
	float2(0.f, 0.f),
	float2(1.f, 0.f),
	float2(0.f, 1.f),
	float2(1.f, 1.f)
};

struct VS_INPUT_TEX
{
	float3	vPos	: POSITION;
	float2	vUV		: TEXCOORD;
};

struct VS_OUTPUT_TEX
{
	float4	vPos	: SV_POSITION;
	float2	vUV		: TEXCOORD;
};

VS_OUTPUT_TEX FullScreenVS(uint iVertexID : SV_VertexID)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	output.vPos = float4(g_vNullPos[iVertexID], 0.f, 1.f);
	output.vUV = g_vNullUV[iVertexID];

	return output;
}