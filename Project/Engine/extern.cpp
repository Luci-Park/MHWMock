#include "pch.h"
#include "global.h"

tTransform g_transform = {};
tGlobal GlobalData = {};



extern const char* RES_TYPE_STR[(UINT)RES_TYPE::END] =
{
	"MATERIAL",
	"PREFAB",
	"MODEL",
	"MESH",
	"TEXTURE",
	"ANIMATION",
	"SOUND",
	"GRAPHICS_SHADER",
	"COMPUTE_SHADER"
};

extern const wchar_t* RES_TYPE_WSTR[(UINT)RES_TYPE::END] =
{
	L"MATERIAL",
	L"PREFAB",
	L"MODEL",
	L"MESH",
	L"TEXTURE",
	L"ANIMATION",
	L"SOUND",
	L"GRAPHICS_SHADER",
	L"COMPUTE_SHADER"
};



extern const char* COMPONENT_TYPE_STR[(UINT)COMPONENT_TYPE::END] =
{
	"TRANSFORM",
	"COLLIDER2D",
	"COLLIDER3D",
	"ANIMATOR2D",
	"ANIMATOR3D",
	"LIGHT2D",
	"LIGHT3D",
	"CAMERA",
	"MESHRENDER",
	"SKINNEDMESHRENDER",
	"PARTICLESYSTEM",
	"TILEMAP",
	"LANDSCAPE",
	"SKYBOX",
	"DECAL",
	"BONEHOLDER",
	"CANVAS",
};

extern const wchar_t* COMPONENT_TYPE_WSTR[(UINT)COMPONENT_TYPE::END] =
{
	L"TRANSFORM",
	L"COLLIDER2D",
	L"COLLIDER3D",
	L"ANIMATOR2D",
	L"ANIMATOR3D",
	L"LIGHT2D",
	L"LIGHT3D",
	L"CAMERA",
	L"MESHRENDER",
	L"SKINNEDMESHRENDER",
	L"PARTICLESYSTEM",
	L"TILEMAP",
	L"LANDSCAPE",
	L"SKYBOX",
	L"DECAL",
	L"BONEHOLDER",
	L"CANVAS",
};

extern const char* LAYER_TYPE_STR[(UINT)LAYER_TYPE::END] =
{
	"Default",
	"Tile",
	"Player",
	"Monster",
	"PlayerProjectile",
	"MonsterProjectile",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"ViewPort UI",
};

extern const wchar_t* LAYER_TYPE_WSTR[(UINT)LAYER_TYPE::END] =
{
	L"Default",
	L"Tile",
	L"Player",
	L"Monster",
	L"PlayerProjectile",
	L"MonsterProjectile",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"ViewPort UI",
};