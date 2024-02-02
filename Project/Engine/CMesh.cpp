#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CStructuredBuffer.h"
#include "CModel.h"
#include <assimp/scene.h>
#include "Assimp.hpp"


CMesh::CMesh(bool _bEngine)
	: CRes(RES_TYPE::MESH, _bEngine)
	, m_tVBDesc{}
	, m_VtxCount(0)
	, m_tIBDesc{}
	, m_IdxCount(0)
	, m_pVtxSys(nullptr)
	, m_pIdxSys(nullptr)
	, m_vecBones(0)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_pVtxSys)
		delete m_pVtxSys;

	if (nullptr != m_pIdxSys)
		delete m_pIdxSys;

	if (nullptr != m_pBoneOffset)
		delete m_pBoneOffset;
}

CMesh* CMesh::CreateFromAssimp(aiMesh* _aiMesh, CModel* _pModel)
{
	wstring wstrName = aiStrToWstr(_aiMesh->mName);

	CMesh* pMesh = new CMesh(true);
	pMesh->SetName(wstrName);

	vector<Vtx> vecVtx(_aiMesh->mNumVertices);
	vector<UINT> vecIdx;
	vecIdx.reserve(_aiMesh->mNumFaces * 3);

	for (int i = 0; i < _aiMesh->mNumVertices; i++)
	{
		if (_aiMesh->HasPositions())
		{
			vecVtx[i].vPos = aiVec3ToVec3(_aiMesh->mVertices[i]);
			pMesh->m_vecVerticies.push_back(vecVtx[i].vPos);
		}
		if (_aiMesh->HasVertexColors(i))
			vecVtx[i].vColor = aiColorToVec4(_aiMesh->mColors[i][0]);
		if (_aiMesh->HasTextureCoords(i))
		{
			vecVtx[i].vUV = Vec2(_aiMesh->mTextureCoords[0][i].x, _aiMesh->mTextureCoords[0][i].y);
		}

		if (_aiMesh->HasNormals())
			vecVtx[i].vNormal = aiVec3ToVec3(_aiMesh->mNormals[i]);
		if (_aiMesh->HasTangentsAndBitangents())
		{
			vecVtx[i].vTangent = aiVec3ToVec3(_aiMesh->mTangents[i]);
			vecVtx[i].vBinormal = aiVec3ToVec3(_aiMesh->mBitangents[i]);
		}
	}

	if (_aiMesh->HasBones())
	{
		pMesh->m_vecBones.resize(_aiMesh->mNumBones);
		vector<Matrix>vecOffset(_aiMesh->mNumBones);
		for (int i = 0; i < _aiMesh->mNumBones; i++)
		{
			aiBone* pBone = _aiMesh->mBones[i];
			pMesh->m_vecBones[i] = aiStrToWstr(pBone->mName);
			_pModel->AddBoneName(aiStrToWstr(pBone->mName));

			vecOffset[i] = aiMatToMat(pBone->mOffsetMatrix).Transpose();
			for (int j = 0; j < pBone->mNumWeights; j++)
			{
				int idx = pBone->mWeights[j].mVertexId;
				
				for (int k = 0; k <= 4; k++)
				{
					assert(k < 4);
					if (vecVtx[idx].vWeights[k] <= 0)
					{
						vecVtx[idx].vIndices[k] = i;
						vecVtx[idx].vWeights[k] = pBone->mWeights[j].mWeight;
						break;
					}
				}
			}
		}
		pMesh->m_pBoneOffset = new CStructuredBuffer;
		pMesh->m_pBoneOffset->Create(sizeof(Matrix), (UINT)vecOffset.size(), SB_TYPE::READ_ONLY, false, vecOffset.data());
	}
	for (int i = 0; i < _aiMesh->mNumFaces; i++)
	{
		vecIdx.push_back(_aiMesh->mFaces[i].mIndices[0]);
		vecIdx.push_back(_aiMesh->mFaces[i].mIndices[1]);
		vecIdx.push_back(_aiMesh->mFaces[i].mIndices[2]);
	}


	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
	return pMesh;
}

void CMesh::Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount)
{
	m_VtxCount = _iVtxCount;
	m_IdxCount = _IdxCount;

	// SystemMem 데이터 복사
	m_pVtxSys = new Vtx[m_VtxCount];
	memcpy(m_pVtxSys, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_pIdxSys = new UINT[m_IdxCount];
	memcpy(m_pIdxSys, _IdxSysMem, sizeof(UINT) * m_IdxCount);
	

	// Vertex 버퍼 생성
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;
	m_tVBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;
	
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSub, m_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// Index 버퍼 생성
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.CPUAccessFlags = 0;
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;	
	m_tIBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;
	
	tSub.pSysMem = _IdxSysMem;
	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSub, m_IB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CMesh::UpdateData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);

	if(m_pBoneOffset)
		m_pBoneOffset->UpdateData(29, PIPELINE_STAGE::PS_VERTEX);
}

void CMesh::render()
{
	UpdateData();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}

void CMesh::render_particle(UINT _iParticleCount)
{
	UpdateData();

	// 인스턴싱
	CONTEXT->DrawIndexedInstanced(m_IdxCount, _iParticleCount, 0, 0, 0);
}

int CMesh::Load(const wstring& _strFilePath)
{
	// 읽기모드로 파일열기
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");
	if (nullptr != pFile)
	{
		// 키값, 상대경로
		wstring strName, strKey, strRelativePath;
		LoadWString(strName, pFile);
		LoadWString(strKey, pFile);
		LoadWString(strRelativePath, pFile);

		SetName(strName);
		SetKey(strKey);
		SetRelativePath(strRelativePath);

		// 정점데이터
		UINT iByteSize = 0;
		fread(&iByteSize, sizeof(int), 1, pFile);
		if (iByteSize == 0)
		{
			fclose(pFile);
			return E_FAIL;
		}
		m_pVtxSys = (Vtx*)malloc(iByteSize);
		fread(m_pVtxSys, 1, iByteSize, pFile);

		m_VtxCount = iByteSize / sizeof(Vtx);

		D3D11_BUFFER_DESC tDesc = {};
		tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tDesc.ByteWidth = iByteSize;
		tDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = m_pVtxSys;

		if (FAILED(DEVICE->CreateBuffer(&tDesc, &tSubData, m_VB.GetAddressOf())))
		{
			assert(nullptr);
		}

		// 정점데이터
		fread(&iByteSize, sizeof(int), 1, pFile);

		if (iByteSize == 0)
		{
			fclose(pFile);
			return E_FAIL;
		}

		m_pIdxSys = (UINT*)malloc(iByteSize);
		fread(m_pIdxSys, 1, iByteSize, pFile);

		m_IdxCount = iByteSize / sizeof(UINT);

		m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		m_tIBDesc.CPUAccessFlags = 0;
		m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;
		m_tIBDesc.ByteWidth = iByteSize; //sizeof(UINT) * m_IdxCount;

		tSubData.pSysMem = m_pIdxSys;
		if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSubData, m_IB.GetAddressOf())))
		{
			assert(nullptr);
		}

		fclose(pFile);
		return S_OK;
	}
	return E_FAIL;
}

int CMesh::Save(const wstring& _strRelativePath)
{
	// 상대경로 저장
	SetRelativePath(_strRelativePath);

	// 파일 경로 만들기
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;

	path parentFolder(strFilePath);
	filesystem::create_directories(parentFolder.parent_path());

	// 파일 쓰기모드로 열기
	FILE* pFile = nullptr;
	errno_t err = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// 키값, 상대 경로	
	SaveWString(GetName(), pFile);
	SaveWString(GetKey(), pFile);
	SaveWString(GetRelativePath(), pFile);

	// 정점 데이터 저장				
	int iByteSize = m_tVBDesc.ByteWidth;
	fwrite(&iByteSize, sizeof(int), 1, pFile);
	fwrite(m_pVtxSys, iByteSize, 1, pFile);

	// 인덱스 정보
	iByteSize = m_tIBDesc.ByteWidth;
	fwrite(&iByteSize, sizeof(int), 1, pFile);
	fwrite(m_pIdxSys, iByteSize, 1, pFile);

	fclose(pFile);


	return S_OK;
	
}