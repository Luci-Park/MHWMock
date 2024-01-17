#include "pch.h"
#include "CModel.h"
#include "CResMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CPathMgr.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

CModel::CModel()
	:CRes(RES_TYPE::MODEL)
{
}

CModel::~CModel()
{
	if (m_pRootNode != nullptr)
	{
		delete m_pRootNode;
		m_pRootNode = nullptr;
	}
}

Ptr<CModel> CModel::LoadFromFbx(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;
	string strFilename(_strRelativePath.begin(), _strRelativePath.end());
	
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(strFilename
		, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast
		| aiProcess_PopulateArmatureData | aiProcess_OptimizeGraph);

	assert(!(!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode));
	
	path filepath(_strRelativePath);
	Ptr<CModel> pModel = new CModel();
	pModel->SetName(filepath.stem());
	wstring strTopKey = filepath.parent_path() / filepath.stem();
	pModel->SetKey(strTopKey + L".model");

	pModel->m_vecMeshes.resize(pScene->mNumMeshes);
	for (int i = 0; i < pScene->mNumMeshes; i++)
	{
		Ptr<CMesh> pMesh = CMesh::CreateFromAssimp(pScene->mMeshes[i]);
		if (nullptr != pMesh)
		{
			pModel->m_vecMeshes[i] = pMesh;
			wstring strMeshKey = strTopKey + L"\\mesh\\" + pMesh->GetName() + L".mesh";

			CResMgr::GetInst()->AddRes<CMesh>(strMeshKey, pMesh);
			//pMesh->Save(strMeshKey);
		}
		else
		{
			return nullptr;
		}
	}

	pModel->m_vecMaterials.resize(pScene->mNumMaterials);
	for (int i = 0; i < pScene->mNumMaterials; i++)
	{
		Ptr<CMaterial> pNewMtrl = new CMaterial(true);
		string strName = pScene->mMaterials[i]->GetName().C_Str();
		wstring wstrName(strName.begin(), strName.end());
		pNewMtrl->SetName(wstrName);

		wstring strMtrlKey = strTopKey + L"\\material\\" + wstrName + L".mtrl";
		//pNewMtrl->Save(strMtrlKey);
	}

	pModel->m_pRootNode = tModelNode::CreateFromAssimp(pScene, pScene->mRootNode, pModel);

	return pModel;
}

void CModel::CreateGameObjectFromModel()
{
	m_pRootNode->CreateGameObjectFromNode();
}

int CModel::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	path parentFolder(strFilePath);
	filesystem::create_directories(parentFolder.parent_path());
	
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile != nullptr)
	{
		SaveWString(GetName(), pFile);
		SaveWString(GetKey(), pFile);

		UINT iSize = m_vecMeshes.size();
		fwrite(&iSize, sizeof(UINT), 1, pFile);
		for (int i = 0; i < m_vecMeshes.size(); i++)
		{
			SaveResRef(m_vecMeshes[i].Get(), pFile);
		}

		iSize = m_vecMaterials.size();
		fwrite(&iSize, sizeof(UINT), 1, pFile);
		for (size_t i = 0; i < m_vecMaterials.size(); i++)
		{
			SaveResRef(m_vecMaterials[i].Get(), pFile);
		}

		if (FAILED(m_pRootNode->Save(pFile)))
		{
			MessageBox(nullptr, L"리소스 저장 실패", L"Model Node 저장 실패", MB_OK);
		}

		fclose(pFile);

		return S_OK;
	}
	else
		return E_FAIL;
}
int CModel::Load(const wstring& _strFilePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (pFile != nullptr)
	{
		wstring str;
		LoadWString(str, pFile);
		SetName(str);
		LoadWString(str, pFile);
		SetKey(str);

		UINT iSize;
		fread(&iSize, sizeof(UINT), 1, pFile);
		m_vecMeshes.resize(iSize);
		for (int i = 0; i < m_vecMeshes.size(); i++)
		{
			LoadResRef(m_vecMeshes[i], pFile);
		}

		iSize;
		fread(&iSize, sizeof(UINT), 1, pFile);
		m_vecMaterials.resize(iSize);
		for (size_t i = 0; i < m_vecMaterials.size(); i++)
		{
			LoadResRef(m_vecMaterials[i], pFile);
		}

		m_pRootNode = new tModelNode;
		if (FAILED(m_pRootNode->Load(pFile)))
		{
			MessageBox(nullptr, L"리소스 로드 실패", L"Model Node 로드 실패", MB_OK);
		}

		fclose(pFile);

		return S_OK;
	}
	else
		return E_FAIL;
}

tModelNode::~tModelNode()
{
	Safe_Del_Vec(vecChildren);
}

int tModelNode::Save(FILE* _File)
{
	SaveWString(strName, _File);
	fwrite(&vPos, sizeof(Vec3), 1, _File);
	fwrite(&vRot, sizeof(Vec3), 1, _File);
	fwrite(&vScale, sizeof(Vec3), 1, _File);
	SaveResRef(pMesh.Get(), _File);
	SaveResRef(pMaterial.Get() , _File);
	for (int i = 0; i < vecChildren.size(); i++)
		vecChildren[i]->Save(_File);
	return S_OK;
}

int tModelNode::Load(FILE* _File)
{
	try
	{
		LoadWString(strName, _File);
		fread(&vPos, sizeof(Vec3), 1, _File);
		fread(&vRot, sizeof(Vec3), 1, _File);
		fread(&vScale, sizeof(Vec3), 1, _File);
		LoadResRef(pMesh, _File);
		LoadResRef(pMaterial, _File);
		for (int i = 0; i < vecChildren.size(); i++)
		{
			tModelNode* pNewChild = new tModelNode();
			pNewChild->Load(_File);
			vecChildren.push_back(pNewChild);
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
	string strTemp = _aiNode->mName.C_Str();
	pNewNode->strName = wstring(strTemp.begin(), strTemp.end());

	aiVector3t<float> scale, rot, pos;
	_aiNode->mTransformation.Decompose(scale, rot, pos);
	pNewNode->vPos = Vec3(pos.x, pos.y, pos.z);
	pNewNode->vRot = Vec3(rot.x, rot.y, rot.z);
	pNewNode->vScale = Vec3(scale.x, scale.y, scale.z);

	if (_aiNode->mNumMeshes > 0)
	{
		if (1 == (UINT)_aiNode->mMeshes)
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
			}
		}
	}

	for (size_t i = 0; i < _aiNode->mNumChildren; i++)
	{
		pNewNode->vecChildren.push_back(CreateFromAssimp(_aiScene, _aiNode->mChildren[i], _pModel));
	}
	return pNewNode;
}

void tModelNode::CreateGameObjectFromNode(CGameObject* _pParent)
{
	CGameObject* pGameObject = new CGameObject;
	pGameObject->SetName(strName);
	pGameObject->SetParent(_pParent);

	pGameObject->AddComponent(new CTransform);
	pGameObject->Transform()->SetRelativePos(vPos);
	pGameObject->Transform()->SetRelativePos(vRot);
	pGameObject->Transform()->SetRelativePos(vScale);

	if (pMesh != nullptr)
	{
		pGameObject->AddComponent(new CMeshRender);
		pGameObject->MeshRender()->SetMesh(pMesh);
		pGameObject->MeshRender()->SetMaterial(pMaterial);
	}
	SpawnGameObject(pGameObject);
	for (int i = 0; i < vecChildren.size(); i++)
	{
		CreateGameObjectFromNode(pGameObject);
	}
}
