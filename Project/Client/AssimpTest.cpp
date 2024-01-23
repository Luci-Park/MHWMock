#include "pch.h"
#include "AssimpTest.h"

#include <Engine/CMesh.h>
#include <Engine/CResMgr.h>

#include <Engine/CGameObject.h>
#include <Engine/CTransform.h>
#include <Engine/CMeshRender.h>

void TestAssimp()
{
	Assimp::Importer importer;
	string filename = "C:\\Users\\user\\Documents\\_Quve17\\Luci\\Coding\\AssortRock\\MHWMock\\anjanath\\anjanath_body_w_Anim.fbx";
	//string filename = "C:\\Users\\dream\\Downloads\\anjanath_body_w_Anim.fbx";

	path filepath(filename);
	wstring a = filepath.stem();
	wstring b = filepath.parent_path() / filepath.stem();

	const aiScene* scene = importer.ReadFile(filename
		, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast
		| aiProcess_PopulateArmatureData | aiProcess_OptimizeGraph);

	assert(!(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode));
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		ExportMesh(scene->mMeshes[i]);
	}
	for (int i = 0; i < scene->mNumSkeletons; i++)
	{
		ProcessSkeleton(scene->mSkeletons[i]);
	}
}

void ExportMesh(aiMesh* _aiMesh)
{
	string strName = _aiMesh->mName.C_Str();
	wstring wstrName(strName.begin(), strName.end());

	vector<Vtx> vecVtx(_aiMesh->mNumVertices);
	vector<UINT> vecIdx(_aiMesh->mNumFaces * 3);

	for (int i = 0; i < _aiMesh->mNumVertices; i++)
	{
		if (_aiMesh->HasPositions())
			vecVtx[i].vPos = Vec3(_aiMesh->mVertices[i].x, _aiMesh->mVertices[i].y, _aiMesh->mVertices[i].z);
		if (_aiMesh->HasVertexColors(i))
			vecVtx[i].vColor = Vec4((_aiMesh->mColors[i][0]).r, (_aiMesh->mColors[i][0]).g, (_aiMesh->mColors[i][0]).b, (_aiMesh->mColors[i][0]).a);
		if (_aiMesh->HasTextureCoords(i))
		{
			vecVtx[i].vUV = Vec2(_aiMesh->mTextureCoords[i][0].x, _aiMesh->mTextureCoords[i][0].y);
		}

		if (_aiMesh->HasNormals())
			vecVtx[i].vNormal = Vec3(_aiMesh->mNormals[i].x, _aiMesh->mNormals[i].y, _aiMesh->mNormals[i].z);
		if (_aiMesh->HasTangentsAndBitangents())
		{
			vecVtx[i].vNormal = Vec3(_aiMesh->mTangents[i].x, _aiMesh->mTangents[i].y, _aiMesh->mTangents[i].z);
			vecVtx[i].vBinormal = Vec3(_aiMesh->mBitangents[i].x, _aiMesh->mBitangents[i].y, _aiMesh->mBitangents[i].z);
		}
	}

	for (int f = 0; f < _aiMesh->mNumFaces; f++)
	{
		for (int i = 0; i < 3; i++)
			vecIdx[f * 3 + i] = _aiMesh->mFaces[f].mIndices[i];
	}

	for (int i = 0; i < _aiMesh->mNumBones; i++)
	{
		assert(_aiMesh->mBones[i]->mName == _aiMesh->mBones[i]->mNode->mName);
		//ProcessBone(_aiMesh->mBones[i]);
	}
	Ptr<CMesh> pMesh = new CMesh(true);
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
	CResMgr::GetInst()->AddRes(wstrName, pMesh);

}

void ExportTexture(aiTexture* _aiTexture)
{
}

void ExportMaterial(aiMaterial* _aiMaterial)
{
	string strName = _aiMaterial->GetName().C_Str();
	wstring wstrName(strName.begin(), strName.end());
	//for (int i = 0; i < _aiMaterial->mNumProperties; i++)
	//{
	//	aiMaterialProperty* prop = _aiMaterial->mProperties[i];
	//	OutputDebugStringA(("Property Name: " + string(prop->mKey.C_Str()) + "\n").c_str());
	//	OutputDebugStringA(("Property Type: " + std::to_string((UINT)prop->mType) + "\n").c_str());
	//}
}

void ExportAnimation(aiAnimation* _aiAnimation)
{
	string strName = _aiAnimation->mName.C_Str();
	wstring wstrName(strName.begin(), strName.end());
	for (int i = 0; i < _aiAnimation->mNumChannels; i++)
	{
	}
}

void ProcessBone(aiBone* _aiBone)
{
	string bug = "======================================\n";
	OutputDebugStringA(bug.c_str());
	string output = _aiBone->mName.C_Str();
	output += "\n";
	output += _aiBone->mArmature->mName.C_Str();
	output += "\n";
	output += _aiBone->mNode->mName.C_Str();
	output += "\n";
	OutputDebugStringA(output.c_str());
	OutputDebugStringA(bug.c_str());
}

void ProcessSkeleton(aiSkeleton* _aiSkeleton)
{
	OutputDebugStringA("========================\n");
	OutputDebugStringA(_aiSkeleton->mName.C_Str());
	OutputDebugStringA("\n\n");
	for (size_t i = 0; i < _aiSkeleton->mNumBones; i++)
	{
		auto bone = _aiSkeleton->mBones[i];
		string str = "name = ";
		str += bone->mArmature->mName.C_Str();
		str += "\n";
		str += bone->mMeshId->mName.C_Str();
		str += "\n";
		OutputDebugStringA(str.c_str());
		OutputDebugStringA("========================\n");
	}
	OutputDebugStringA("========================\n");
}
