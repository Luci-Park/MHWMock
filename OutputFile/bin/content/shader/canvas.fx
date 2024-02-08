#ifndef _CANVAS
#define _CANVAS

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

#define INTEX   g_tex_0

// ============================
// CANVAS
// RasterizerState      : None
// BlendState           : Mask
// DepthStencilState    : Less
//
// g_tex_0              : Input Texture
// g_tex_1              : Output Texture
// ============================
VS_OUT VS_Canvas(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
        
    return output;
}

struct PS_OUT
{
    float4 UITarget : SV_Target0;
};

// 레스터라이저 스테이트
PS_OUT PS_Canvas(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT)0.f;
    
    output.UITarget = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_btex_0)
    {
        output.UITarget = INTEX.Sample(g_sam_0, _in.vUV);
    }
    
    return output;
}
#endif