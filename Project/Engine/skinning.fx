#ifndef _SKINNING
#define _SKINNING

#include "value.fx"
#include "func.fx"

#define BMLTEX  g_tex_0
#define BMTEX   g_tex_1
#define CMMTEX  g_tex_2
#define NMTEX   g_tex_3
#define EMTEX   g_tex_4
#define RMTTEX  g_tex_5
#define FMTEX   g_tex_6
#define XMTEX   g_tex_7

#define ISBMLTEX    g_btex_0
#define ISBMTEX     g_btex_1
#define ISCMMTEX    g_btex_2
#define ISNMTEX     g_btex_3
#define ISEMTEX     g_btex_4
#define ISRMTTEX    g_btex_5
#define ISFMTEX     g_btex_6
#define ISXMTEX     g_btex_7

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;
    
    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
        
    float3 vViewPos : POSITION;
    
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
};

// ===============
// SKINING
// DOMAIN : Deferred
// MRT    : DEFERRED MRT
// Rasterizer State     : CULL_BACK
// DepthStencil State   : LESS
// Blend State          : Default

// Parameter
#define     SpecCoeff   g_float_0
#define     BoneCount   g_anim_0
// ===============

VS_OUT vert(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
     
    if (BoneCount > 0)
    {
        Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices);
        output.vViewPos = mul(float4(_in.vPos, 1.f), g_matView);
    
        output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matView)).xyz;
        output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matView)).xyz;
        output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matView)).xyz;
             
        output.vPosition = mul(float4(_in.vPos, 1.f), mul(g_matView, g_matProj));
        output.vUV = _in.vUV;
    }
    else
    {
        output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    
        output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
        output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
        output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;
             
        output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
        output.vUV = _in.vUV;
    }
    return output;
}


struct PS_OUT
{
    float4 vColor : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
    float4 vEmissive : SV_Target3;
    float4 vData : SV_Target4;
};

PS_OUT frag(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
   
    output.vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    float roughness = 1.f;
    float metalness = 1.f;
    float translucency = 1.f;
    
    
    
    float3 vViewNormal = _in.vViewNormal;
    
    //if have BML tex ( color tex no transparent )
    if (ISBMLTEX && !ISBMTEX)
    {
        output.vColor = BMLTEX.Sample(g_sam_0, _in.vUV);
    }
    
    //if have BM tex ( color tex R channel is alpha )
    if (ISBMTEX && !ISBMLTEX)
    {
        output.vColor = (float4)0.f;
        float3 color = BMTEX.Sample(g_sam_0, _in.vUV);
        output.vColor.rgb = color.rgb;
        output.vColor.a = color.r;
    }
    
    if(ISRMTTEX)
    {
        float4 RMTcolor = RMTTEX.Sample(g_sam_0, _in.vUV);
        
        //Channel R is Roughness
        //Channel G is Metalness
        //Channel B is translucency
        float roughness = 1.0f- RMTcolor.r;
        float metalness = RMTcolor.g;
        float translucency = RMTcolor.b;
        
        output.vColor.a = translucency;
    }
    
    //if have normal tex
    if (ISNMTEX)
    {
        //2-channel tangent space normal map
        float2 normalMapColor = NMTEX.Sample(g_sam_0, _in.vUV);
        float2 normalXY = normalMapColor * 2.0f - 1.0f;
        
        float z = sqrt(1.0f - saturate(dot(normalXY, normalXY)));
        
        float3 vNormal = float3(normalXY, z);
        vNormal.y *= -1;
        
        float3x3 vRotateMat =
        {
            _in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal     
        };
        
        vViewNormal = normalize(mul(vNormal, vRotateMat));
    }
    
    //If have emissive texture
    if(ISEMTEX)
    {
        float4 emissive = EMTEX.Sample(g_sam_0, _in.vUV);
        
        output.vEmissive = output.vColor * emissive;
    }
    
    
    
    output.vNormal = float4(vViewNormal, 1.f);
    output.vPosition = float4(_in.vViewPos, 1.f);
    output.vData = float4(0.f, 0.f, 0.f, 1.f);
        
    output.vColor.a = saturate(SpecCoeff);
    
    return output;
}






#endif