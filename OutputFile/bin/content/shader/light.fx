#ifndef _LIGHT
#define _LIGHT

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vPos : POSITION;    
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
};

struct PS_OUT
{
    float4 vDiffuse : SV_Target0;
    float4 vSpecular : SV_Target1;
};

// =====================================
// DirLightShader
// MRT              : LIGHT
// Mesh             : RectMesh
// Rasterizer       : CULL_BACK
// DepthStencil     : NO_TEST_NO_WRITE
// Blend            : ONE_ONE

// Parameter
#define NormalTargetTex     g_tex_0
#define PoisitionTargetTex  g_tex_1
#define LightIdx            g_int_0
// =====================================

VS_OUT VS_DirLightShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ����ϴ� �޽��� RectMesh(���� �����̽����� ������ 0.5 ¥�� ���簢��)
    // ���� 2��� Ű���� ȭ�� ��ü�� �ȼ����̴��� ȣ��� �� �ְ� �Ѵ�.
    output.vPosition = float4(_in.vPos.xyz * 2.f, 1.f);
    
    return output;
}


PS_OUT PS_DirLightShader(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float2 vScreenUV = _in.vPosition.xy / g_Resolution.xy;    
    float3 vViewPos = PoisitionTargetTex.Sample(g_sam_0, vScreenUV).xyz;
    float3 vViewNormal = NormalTargetTex.Sample(g_sam_0, vScreenUV).xyz;
    
    // �ȼ� ��ġ�� ������ UV ��ġ���� Position ���� �����Դµ�, �ش� ������ ��ϵ� ��ü�� ����.
    if (vViewPos.x == 0.f && vViewPos.y == 0.f && vViewPos.z == 0.f)
    {
        discard;
        //output.vDiffuse = float4(0.2f, 1.f, 0.2f, 1.f);
        //output.vSpecular = float4(0.2f, 1.f, 0.2f, 1.f);
        //return output;
    }
    
    // ���� ��� ����� ���� ���� ����
    tLightColor LightColor = (tLightColor) 0.f;
    float fSpecPow = 0.f;
    
    // ���� ������ ������ LightBuffer ������ ��� �ִ��� �ε����� �Է�
    // ���� �־��� ��ü�� ��ġ���� �븻���� Ÿ�� �ؽ��Ŀ��� �����ͼ� �Է�
    CalcLight3D(vViewPos, vViewNormal, LightIdx, LightColor, fSpecPow);

    // ���� ���� ������ ���⸦ �� Ÿ��(Diffuse, Specular) �� ���
    output.vDiffuse = LightColor.vDiffuse + LightColor.vAmbient;    
    output.vSpecular = g_Light3DBuffer[LightIdx].Color.vDiffuse * fSpecPow;
        
    output.vDiffuse.a = 1.f;
    output.vSpecular.a = 1.f;
    
    return output;
}



// =====================================
// MergeShader
// MRT              : SwapChain
// Domain           : DOMAIN_LIGHT
// Mesh             : RectMesh
// Rasterizer       : CULL_BACK
// DepthStencil     : NO_TEST_NO_WRITE
// Blend            : Default

// Parameter
#define ColorTargetTex    g_tex_0
#define DiffuseTargetTex  g_tex_1
#define SpecularTargetTex g_tex_2
#define EmissiveTargetTex g_tex_3
// =====================================
VS_OUT VS_MergeShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ����ϴ� �޽��� RectMesh(���� �����̽����� ������ 0.5 ¥�� ���簢��)
    // ���� 2��� Ű���� ȭ�� ��ü�� �ȼ����̴��� ȣ��� �� �ְ� �Ѵ�.
    output.vPosition = float4(_in.vPos.xyz * 2.f, 1.f);
    
    return output;
}


float4 PS_MergeShader(VS_OUT _in) : SV_Target
{
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float2 vScreenUV =  _in.vPosition.xy / g_Resolution.xy;
        
    float4 vColor = ColorTargetTex.Sample(g_sam_0, vScreenUV);
    float4 vDiffuse = DiffuseTargetTex.Sample(g_sam_0, vScreenUV);
    float4 vSpecular = SpecularTargetTex.Sample(g_sam_0, vScreenUV);
    float4 vEmissive = EmissiveTargetTex.Sample(g_sam_0, vScreenUV);
    
    vOutColor.xyz = vColor.xyz * vDiffuse.xyz + (vSpecular.xyz * vColor.a) + vEmissive.xyz;
    vOutColor.a = 1.f;
    
    return vOutColor;
}

#endif