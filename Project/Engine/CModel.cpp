#include "pch.h"
#include "CModel.h"
#include "CResMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CPathMgr.h"

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
			pMesh->Save(strMeshKey);
		}
		else
		{
			return nullptr;
		}
	}

	pModel->m_vecMaterials.resize(pScene->mNumMaterials);
	for (int i = 0; i < pScene->mNumMaterials; i++)
	{
		Ptr<CMaterial> pNewMtrl = new CMaterial;
		string strName = pScene->mMaterials[i]->GetName().C_Str();
		wstring wstrName(strName.begin(), strName.end());
		pNewMtrl->SetName(wstrName);

		wstring strMtrlKey = strTopKey + L"\\material\\" + wstrName + L".mtrl";
		pNewMtrl->Save(strMtrlKey);
	}

	pModel->m_pRootNode = tModelNode::CreateFromAssimp(pScene, pScene->mRootNode, pModel);

	return pModel;
}

int CModel::Load(const wstring& _strFilePath)
{
	return S_OK;
}

tModelNode::~tModelNode()
{
	Safe_Del_Vec(vecChildren);
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
