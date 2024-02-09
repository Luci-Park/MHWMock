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
    float4 vLocalPosition : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

#define InputTex   g_tex_0

// =======================================
// CANVAS
// RasterizerState      : None
// BlendState           : Mask
// DepthStencilState    : Less
//
// g_tex_0              : Input Texture
// =======================================
VS_OUT VS_Canvas(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    //output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    //output.vPosition = float4(_in.vLocalPos, 1.f);
    output.vPosition = mul(float4(_in.vLocalPos, 1.f),g_matWVP);
    output.vUV = _in.vUV;
        
    return output;
}

struct PS_OUT
{
    float4 CanvasTex : SV_Target0;
};

PS_OUT PS_Canvas(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT)0.f;
    output.CanvasTex = float4(1.f, 0.f, 1.f, 1.f);
    
    //float4 output = (float4) 0.f;
    
    if (g_btex_0)
    {
        //output = InputTex.Sample(g_sam_0,_in.vUV);
        output.CanvasTex = InputTex.Sample(g_sam_0, _in.vUV);
    }
    //output.CanvasTex.a = 1.f;
    //output.a = 1.0f;
    return output;
}
#endif