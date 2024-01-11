#include "pch.h"
#include "AssimpTest.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Engine/CMesh.h>
#include <Engine/CResMgr.h>

void TestAssimp()
{
	Assimp::Importer importer;
	//string filename = "C:\\Users\\user\\Documents\\_Quve17\\Luci\\Coding\\AssortRock\\MHWMock\\anjanath\\anjanath_body_w_Anim.fbx";
	string filename = "C:\\Users\\dream\\Downloads\\anjanath_body_w_Anim.fbx";

	const aiScene* scene = importer.ReadFile(filename
		, aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices
		| aiProcess_MakeLeftHanded | aiProcess_Triangulate | aiProcess_ValidateDataStructure
		| aiProcess_PopulateArmatureData | aiProcess_OptimizeGraph);

	assert(!(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode));

	string strModelName = scene->mName.C_Str();
	wstring wstrModelName(strModelName.begin(), strModelName.end());
	for (int m = 0; m < scene->mNumMeshes; m++)
	{
		aiMesh* aMesh = scene->mMeshes[m];
		string strMeshName = aMesh->mName.C_Str();
		wstring wstrMeshName(strMeshName.begin(), strMeshName.end());
		wstrMeshName = wstrModelName + L"/" + wstrMeshName;

		vector<Vtx> vecVtx(aMesh->mNumVertices);
		vector<UINT> vecIdx(aMesh->mNumFaces * 3);

		for (int v = 0; v < aMesh->mNumVertices; v++)
		{
			if (aMesh->HasPositions())
				vecVtx[v].vPos = Vec3(aMesh->mVertices[v].x, aMesh->mVertices[v].y, aMesh->mVertices[v].z);
			if (aMesh->HasVertexColors(v))
				vecVtx[v].vColor = Vec4((aMesh->mColors[v][0]).r, (aMesh->mColors[v][0]).g, (aMesh->mColors[v][0]).b, (aMesh->mColors[v][0]).a);
			if (aMesh->HasTextureCoords(v))
				vecVtx[v].vUV = Vec2(aMesh->mTextureCoords[v][0].x, aMesh->mTextureCoords[v][0].y);

			if (aMesh->HasNormals())
				vecVtx[v].vNormal = Vec3(aMesh->mNormals[v].x, aMesh->mNormals[v].y, aMesh->mNormals[v].z);
			if (aMesh->HasTangentsAndBitangents())
			{
				vecVtx[v].vNormal = Vec3(aMesh->mTangents[v].x, aMesh->mTangents[v].y, aMesh->mTangents[v].z);
				vecVtx[v].vBinormal = Vec3(aMesh->mBitangents[v].x, aMesh->mBitangents[v].y, aMesh->mBitangents[v].z);
			}
		}

		for (int f = 0; f < aMesh->mNumFaces; f++)
		{
			for (int i = 0; i < 3; i++)
				vecIdx[f * 3 + i] = aMesh->mFaces[f].mIndices[i];
		}

		Ptr<CMesh> pMesh = new CMesh();
		pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
		CResMgr::GetInst()->AddRes(wstrMeshName, pMesh);
		OutputDebugStringW(wstrMeshName.c_str());
	}
}
