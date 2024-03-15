#include "pch.h"
#include "CModel.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CSkinnedMeshRender.h"
#include "CAnimator3D.h"
#include "CAnimationClip.h"
#include "CBoneHolder.h"
#include "CAnimator3D.h"
#include "CStructuredBuffer.h"
#include "Assimp.hpp"


CModel::CModel()
	:CRes(RES_TYPE::MODEL)
{
}

CModel::~CModel()
{
	delete m_pRootNode;
}

Ptr<CModel> CModel::LoadFromFbx(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;
	
	Assimp::Importer importer;
	unsigned int originalFlags = aiProcess_ConvertToLeftHanded | aiProcess_PopulateArmatureData | aiProcess_Triangulate;
	unsigned int excludeFlags = aiProcess_RemoveRedundantMaterials;

	const aiScene* pScene = importer.ReadFile(
		string(strFullPath.begin(), strFullPath.end()),
		originalFlags //& (~excludeFlags)
	);

	assert(!(!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode));
	
	path filepath(_strRelativePath);
	Ptr<CModel> pModel = new CModel;
	pModel->SetName(filepath.stem());
	wstring strRootKey = filepath.parent_path() / filepath.stem();
	strRootKey += L"\\";

	pModel->SetKey(strRootKey + pModel->GetName() + L".model");

	unordered_set<wstring> nameCheck;

	pModel->m_vecMeshes.resize(pScene->mNumMeshes);
	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		Ptr<CMesh> pMesh = CMesh::CreateFromAssimp(pScene->mMeshes[i], pModel.Get());
		
		if (pMesh == nullptr) return nullptr;
		
		int num = 0;
		wstring finName = pMesh->GetName();
		while (nameCheck.find(finName + L".mesh") != nameCheck.end())
			finName = pMesh->GetName() + L" " + std::to_wstring(num++);
		nameCheck.insert(finName + L".mesh");
		pMesh->SetName(finName);
		pModel->m_vecMeshes[i] = pMesh;
	}

	pModel->m_vecMaterials.resize(pScene->mNumMaterials);
	for (int i = 0; i < pScene->mNumMaterials; i++)
	{
		Ptr<CMaterial> pNewMtrl = new CMaterial();
		pNewMtrl->SetShader(CResMgr::GetInst()->FindRes<CGraphicsShader>(L"SkinningShader"));

		int num = 0;
		wstring wstrName = aiStrToWstr(pScene->mMaterials[i]->GetName());
		wstring wstrFinName = wstrName;
		while (nameCheck.find(wstrFinName + L".mtrl") != nameCheck.end())
			wstrFinName = wstrName + L" " + std::to_wstring(num++);
		nameCheck.insert(wstrFinName + L".mtrl");
		pNewMtrl->SetName(wstrFinName);
		pModel->m_vecMaterials[i] = pNewMtrl;
	}

	vector<Ptr<CAnimationClip>> vecClips(pScene->mNumAnimations);
	pModel->m_vecAnimNames.resize(pScene->mNumAnimations);
	for (int i = 0; i < pScene->mNumAnimations; i++)
	{
		Ptr<CAnimationClip> pAnim = CAnimationClip::CreateFromAssimp(pScene->mAnimations[i]);
		if (pAnim == nullptr) return nullptr;

		int num = 0;
		wstring finName = pAnim->GetName();
		while (nameCheck.find(finName + L".anim") != nameCheck.end())
			finName = pAnim->GetName() + L" " + std::to_wstring(num++);
		nameCheck.insert(finName + L".anim");
		pAnim->SetName(finName);
		vecClips[i] = pAnim;
	}

	pModel->m_pRootNode = tModelNode::CreateFromAssimp(pScene, pScene->mRootNode, pModel);

	for (size_t i = 0; i < pModel->m_vecMeshes.size(); i++)
	{
		wstring path = strRootKey + L"mesh\\" + pModel->m_vecMeshes[i]->GetName() + L".mesh";
		assert(pModel->m_vecMeshes[i]->Save(path) == S_OK);
	}
	for (size_t i = 0; i < pModel->m_vecMaterials.size(); i++)
	{
		wstring path = strRootKey + L"material\\" + pModel->m_vecMaterials[i]->GetName() + L".mtrl";
		assert(pModel->m_vecMaterials[i]->Save(path) == S_OK);
	}
	for (size_t i = 0; i < vecClips.size(); i++)
	{
		wstring path = strRootKey + L"anim\\" + vecClips[i]->GetName() + L".anim";
		assert(vecClips[i]->Save(path) == S_OK);
		pModel->m_vecAnimNames[i] = path;
	}
	
	assert(pModel->Save(strRootKey + pModel->GetName() + L".model") == S_OK);

	CResMgr::GetInst()->AddRes<CModel>(pModel->GetKey(), pModel);
	return pModel;
}

void CModel::CreateGameObjectFromModel()
{
	CGameObject* pNewObject = m_pRootNode->SpawnGameObjectFromNode();
	if (m_setBoneNames.size() > 0)
	{
		pNewObject->AddComponent(new CBoneHolder(m_setBoneNames));
	}
	if (m_vecAnimNames.size() > 0)
	{
		pNewObject->AddComponent(new CAnimator3D());
		pNewObject->Animator3D()->SetAnimations(m_vecAnimNames);
	}
	SpawnGameObject(pNewObject);
}

int CModel::Save(const wstring& _strRelativePath)
{
	if (IsEngineRes())
		return E_FAIL;

	SetRelativePath(_strRelativePath);
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;

	path parentFolder(strFilePath);
	filesystem::create_directories(parentFolder.parent_path());
	
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile == nullptr)
		return E_FAIL;

	SaveWString(GetName(), pFile);
	SaveWString(GetKey(), pFile);

	UINT iSize = m_vecMeshes.size();
	fwrite(&iSize, sizeof(UINT), 1, pFile);
	for (int i = 0; i < m_vecMeshes.size(); i++)
		SaveResRef(m_vecMeshes[i].Get(), pFile);

	iSize = m_vecMaterials.size();
	fwrite(&iSize, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < m_vecMaterials.size(); i++)
		SaveResRef(m_vecMaterials[i].Get(), pFile);

	iSize = m_vecAnimNames.size();
	fwrite(&iSize, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < iSize; i++)
		SaveWString(m_vecAnimNames[i], pFile);

	iSize = m_setBoneNames.size();
	fwrite(&iSize, sizeof(UINT), 1, pFile);
	for (auto str : m_setBoneNames)
		SaveWString(str, pFile);

	if (FAILED(m_pRootNode->Save(pFile)))
	{
		MessageBox(nullptr, L"Resource Save Failed", (L"Model Node " + _strRelativePath).c_str(), MB_OK);
	}

	fclose(pFile);
	return S_OK;
}
int CModel::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");
	if (pFile == nullptr)
		return E_FAIL;

	wstring name, key;
	LoadWString(name, pFile);
	LoadWString(key, pFile);

	SetName(name);
	SetKey(key);

	UINT iSize;
	fread(&iSize, sizeof(UINT), 1, pFile);
	m_vecMeshes.resize(iSize);
	for (int i = 0; i < m_vecMeshes.size(); i++)
		LoadResRef(m_vecMeshes[i], pFile);

	fread(&iSize, sizeof(UINT), 1, pFile);
	m_vecMaterials.resize(iSize);
	for (size_t i = 0; i < m_vecMaterials.size(); i++)
		LoadResRef(m_vecMaterials[i], pFile);

	fread(&iSize, sizeof(UINT), 1, pFile);
	m_vecAnimNames.resize(iSize);
	for (size_t i = 0; i < iSize; i++)
		LoadWString(m_vecAnimNames[i], pFile);

	fread(&iSize, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < iSize; i++)
	{
		wstring boneName;
		LoadWString(boneName, pFile);
		m_setBoneNames.insert(boneName);
	}

	m_pRootNode = new tModelNode;

	if (FAILED(m_pRootNode->Load(pFile)))
	{
		MessageBox(nullptr, L"Resource Load Failed", (L"Model Node " + _strFilePath).c_str(), MB_OK);
	}
	fclose(pFile);

	return S_OK;
}

tModelNode::~tModelNode()
{
	Safe_Del_Vec(vecChildren);
}

int tModelNode::Save(FILE* _File)
{
	try
	{
		SaveWString(strName, _File);
		fwrite(&vPos, sizeof(Vec3), 1, _File);
		fwrite(&qRot, sizeof(Quaternion), 1, _File);
		fwrite(&vScale, sizeof(Vec3), 1, _File);
		SaveResRef(pMesh.Get(), _File);
		SaveResRef(pMaterial.Get(), _File);
		int childnum = vecChildren.size();
		fwrite(&childnum, sizeof(int), 1, _File);
		for (int i = 0; i < vecChildren.size(); i++)
			vecChildren[i]->Save(_File);
		return S_OK;
	}
	catch (const std::exception&)
	{
		return E_FAIL;
	}
}

int tModelNode::Load(FILE* _File)
{
	try
	{
		LoadWString(strName, _File);
		fread(&vPos, sizeof(Vec3), 1, _File);
		fread(&qRot, sizeof(Quaternion), 1, _File);
		fread(&vScale, sizeof(Vec3), 1, _File);
		LoadResRef(pMesh, _File);
		LoadResRef(pMaterial, _File);
		int childnum;
		fread(&childnum, sizeof(int), 1, _File);
		vecChildren.resize(childnum);
		for (int i = 0; i < vecChildren.size(); i++)
		{
			tModelNode* pNewChild = new tModelNode();
			pNewChild->Load(_File);
			vecChildren[i] = pNewChild;
		}
		return S_OK;
	}
	catch(const std::exception&)
	{
		return E_FAIL;
	}
}

tModelNode* tModelNode::CreateFromAssimp(const aiScene* _aiScene, aiNode* _aiNode, Ptr<CModel> _pModel)
{
	tModelNode* pNewNode = new tModelNode();
	
	if (_aiNode == _aiScene->mRootNode)
	{
		pNewNode->strName = _pModel->GetName();
	}
	else
	{
		string strTemp = _aiNode->mName.C_Str();
		pNewNode->strName = wstring(strTemp.begin(), strTemp.end());
	}
	aiVector3t<float> scale, position;
	aiQuaterniont<float> rotation;
	_aiNode->mTransformation.Decompose(scale, rotation, position);

	pNewNode->vPos = aiVec3ToVec3(position);
	pNewNode->qRot = aiQuatToQuat(rotation);
	pNewNode->vScale = aiVec3ToVec3(scale);
	
	if (_aiNode->mNumMeshes > 0)
	{
		if (1 == _aiNode->mNumMeshes)
		{
			pNewNode->pMesh = _pModel->GetMesh(_aiNode->mMeshes[0]);
			pNewNode->pMaterial = _pModel->GetMaterial(_aiScene->mMeshes[_aiNode->mMeshes[0]]->mMaterialIndex);
		}
		else
		{
			for (int i = 0; i < _aiNode->mNumMeshes; i++)
			{
				tModelNode* pNewChild = new tModelNode();
				pNewChild->strName = pNewNode->strName + std::to_wstring(i);
				pNewChild->pMesh = _pModel->GetMesh(_aiNode->mMeshes[i]);
				pNewChild->pMaterial = _pModel->GetMaterial(_aiScene->mMeshes[_aiNode->mMeshes[i]]->mMaterialIndex);
				pNewNode->vecChildren.push_back(pNewChild);
			}
		}
	}
	for (size_t i = 0; i < _aiNode->mNumChildren; i++)
	{
		pNewNode->vecChildren.push_back(CreateFromAssimp(_aiScene, _aiNode->mChildren[i], _pModel));
	}
	return pNewNode;
}

CGameObject* tModelNode::CreateGameObjectFromNode()
{
	CGameObject* pGameObject = new CGameObject;
	pGameObject->SetName(strName);

	pGameObject->AddComponent(new CTransform);
	pGameObject->Transform()->SetRelativePos(vPos);
	pGameObject->Transform()->SetRelativeRot(qRot);
	pGameObject->Transform()->SetRelativeScale(vScale);

	if (pMesh != nullptr)
	{
		if (pMesh->HasBones())
			pGameObject->AddComponent(new CSkinnedMeshRender);
		else
			pGameObject->AddComponent(new CMeshRender);

		pGameObject->GetRenderComponent()->SetMesh(pMesh);
		pGameObject->GetRenderComponent()->SetMaterial(pMaterial);
	}
	return pGameObject;
}

CGameObject* tModelNode::SpawnGameObjectFromNode()
{
	CGameObject* pNewGameObject = CreateGameObjectFromNode();
	for (int i = 0; i < vecChildren.size(); i++)
	{
		pNewGameObject->AddChild(vecChildren[i]->SpawnGameObjectFromNode());
	}
	return pNewGameObject;
}

tModelNode* tModelNode::FindNode(wstring _strName)
{
	if (_strName == strName)
		return this;

	for (size_t i = 0; i < vecChildren.size(); i++)
	{
		auto pNode = vecChildren[i]->FindNode(_strName);
		if (pNode) return pNode;
	}
	return nullptr;
}
