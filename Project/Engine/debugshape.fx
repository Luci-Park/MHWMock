#ifndef _DEBUGSHAPE
#define _DEBUGSHAPE

#include "value.fx"

// =================
// DebugShape Shader
// Topology : LineStrip
// RS_TYPE  : CULL_NONE
// DS_TYPE  : NO_TEST_NO_WRITE
// BS_TYPE  : Default

// Parameter
// g_vec4_0 : OutColor
// ==================
//--------------------------------------------------------
//                              Capsule
//--------------------------------------------------------
#define Input_0 g_float_0 //    radius
#define Input_1 g_float_1 //    HalfHeight
#define Input_2 g_float_2 //    NULL
//========================================================

struct VS_DEBUG_IN
{
    float3 vPos : POSITION;    
    float3 vNormal : NORMAL;
};

struct VS_DEBUG_OUT
{
    float4 vPosition : SV_Position;
    
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VS_DEBUG_OUT VS_DebugShape(VS_DEBUG_IN _in)
{
    VS_DEBUG_OUT output = (VS_DEBUG_OUT) 0.f;    
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    
    
    return output;    
}

float4 PS_DebugShape(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = g_vec4_0;
    
    return vOutColor;
}

VS_DEBUG_OUT VS_DebugShape_Capslue(VS_DEBUG_IN _in)
{
    VS_DEBUG_OUT output = (VS_DEBUG_OUT)0.f;

    // 버텍스의 위치를 가져옵니다.
    float3 vertexPos = _in.vPos;

    // 높이의 절반과 반지름을 이용하여 캡슐의 크기를 조정합니다.
    vertexPos.x *= Input_1;
    vertexPos.y *= Input_0;
    vertexPos.z *= Input_1;

    // 출력을 설정합니다.
    output.vPosition = mul(float4(vertexPos, 1), g_matWVP);
    output.vViewNormal = mul(float4(_in.vNormal, 0), g_matWVP).xyz;
   
    return output;
}

float4 PS_DebugShape_Capslue(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = g_vec4_0;
    
    return vOutColor;
}


float4 PS_DebugShape_Sphere(VS_DEBUG_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
        
    float3 vEye = -normalize(_in.vViewPos);        
    float fOutLine = 1.f - saturate(abs(dot(vEye, _in.vViewNormal)));        
    fOutLine = pow(fOutLine, 2.5);
    
    vOutColor = g_vec4_0;
    vOutColor.a = fOutLine;    
    
    return vOutColor;
}







#endif
