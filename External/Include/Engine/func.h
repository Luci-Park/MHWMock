#pragma once

template <typename T, UINT _Size>
void DeleteArray(T* (&Arr)[_Size])
{
	for (UINT i = 0; i < _Size; ++i)
	{
		if (nullptr != Arr[i])
			delete Arr[i];
	}
}



// ������Ʈ ����
class CGameObject;
void SpawnGameObject(CGameObject* _NewObject, Vec3 _vWorldPos, int _LayerIdx);
void SpawnGameObject(CGameObject* _NewObject, Vec3 _vWorldPos, const wstring& _LayerName);
void SpawnGameObject(CGameObject* _NewObject, const wstring& _LayerName);
void SpawnGameObject(CGameObject* _NewObject);

// ������Ʈ ����
void DestroyObject(CGameObject* _DeletObject);

// DrawDebugShape
void DrawDebugRect(Vec3 _vWorldPos, Vec2 _vWorldScale, Vec4 _vColor, Vec3 _vRotation, float _fTime = 0.f, bool DepthTest = false);
void DrawDebugRect(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false);

void DrawDebugCircle(Vec3 _vWorldPos, float _fRadius, Vec4 _vColor, Vec3 _vRotation, float _fTime = 0.f, bool DepthTest = false);
void DrawDebugCircle(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false);

void DrawDebugCube(Vec3 _vWorldPos, float _fRadius, Vec4 _vColor, Vec3 _vRotation, float _fTime = 0.f, bool DepthTest = false);
void DrawDebugCube(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false, Vec3 _HalfExtents = Vec3(0.f, 0.f, 0.f));

void DrawDebugSphere(Vec3 _vWorldPos, float _fRadius, Vec4 _vColor, Vec3 _vRotation, float _fTime = 0.f, bool DepthTest = false);
void DrawDebugSphere(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false);

void DrawDebugLine(Vec3 from, Vec3 to);

void DrawDebugCapsule3D(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false,float _radius = 1.f,float _HalfHeight = 1.f);
void DrawDebugConvex3D(const Matrix& _matWorld, Vec4 _vColor, float _fTime = 0.f, bool DepthTest = false,Vec3 _convexScale = Vec3(1.f,1.f,1.f));

bool IsValidObj(CGameObject*& _Target);


const char* ToString(RES_TYPE);
const wchar_t* ToWSTring(RES_TYPE);

const char* ToString(COMPONENT_TYPE);
const wchar_t* ToWSTring(COMPONENT_TYPE);

const char* ToString(LAYER_TYPE);
const wchar_t* ToWString(LAYER_TYPE);

// Save / Load
void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _File);

class CRes;
template<typename T>
class Ptr;

void SaveResRef(Ptr<CRes> _Res, FILE* _File);

class CResMgr;
template<typename T>
void LoadResRef(Ptr<T>& _Res, FILE* _File)
{
	int i = 0;	
	fread(&i, sizeof(i), 1, _File);
	
	if (i)
	{
		wstring strKey, strRelativePath, strName;
		LoadWString(strKey, _File);
		LoadWString(strRelativePath, _File);
		assert(strKey != L"");

		_Res = CResMgr::GetInst()->Load<T>(strKey, strRelativePath);
	}
}


template<typename T, UINT Size>
void Safe_Del_Array(T* (&arr)[Size])
{
	for (UINT i = 0; i < Size; ++i)
	{
		if (nullptr != arr[i])
			delete arr[i];
	}	
}

template<typename T>
void Safe_Del_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Del_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}

	_map.clear();
}

string WSTR2STR(wstring _string);

wstring STR2WSTR(string _string);

string GetAnimParamStr(AnimParamType _type);
wstring GetAnimParamWStr(AnimParamType _type);

string GetAnimConditionStr(AnimConditionType _type);
wstring GetAnimCondtionWstr(AnimConditionType _type);
