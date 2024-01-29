#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CStructuredBuffer.h"
#include <assimp/scene.h>


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

CMesh* CMesh::CreateFromAssimp(aiMesh* _aiMesh)
{
	string strName = _aiMesh->mName.C_Str();
	wstring wstrName(strName.begin(), strName.end());

	CMesh* pMesh = new CMesh(true);
	pMesh->SetName(wstrName);
	pMesh->SetKey(wstrName);

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
			vecVtx[i].vTangent = Vec3(_aiMesh->mTangents[i].x, _aiMesh->mTangents[i].y, _aiMesh->mTangents[i].z);
			vecVtx[i].vBinormal = Vec3(_aiMesh->mBitangents[i].x, _aiMesh->mBitangents[i].y, _aiMesh->mBitangents[i].z);
		}
	}

	if (_aiMesh->HasBones())
	{
		pMesh->m_vecBones.resize(_aiMesh->mNumBones);
		vector<Matrix>vecOffset(_aiMesh->mNumBones);
		for (int i = 0; i < _aiMesh->mNumBones; i++)
		{
			aiBone* pBone = _aiMesh->mBones[i];
			string name = pBone->mName.C_Str();
			pMesh->m_vecBones[i] = wstring(name.begin(), name.end());

			vecOffset[i] = XMLoadFloat4x4(reinterpret_cast<const XMFLOAT4X4*>(&pBone->mOffsetMatrix));
			for (int j = 0; j < pBone->mNumWeights; j++)
			{
				int idx = pBone->mWeights[j].mVertexId;
				for (int k = 0; k < 4; k++)
				{
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
	for (int f = 0; f < _aiMesh->mNumFaces; f++)
	{
		for (int i = 0; i < 3; i++)
			vecIdx[f * 3 + i] = _aiMesh->mFaces[f].mIndices[i];
	}


	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
	return pMesh;
}

void CMesh::Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount)
{
	m_VtxCount = _iVtxCount;
	m_IdxCount = _IdxCount;

	// SystemMem ������ ����
	m_pVtxSys = new Vtx[m_VtxCount];
	memcpy(m_pVtxSys, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_pIdxSys = new UINT[m_IdxCount];
	memcpy(m_pIdxSys, _IdxSysMem, sizeof(UINT) * m_IdxCount);
	

	// Vertex ���� ����
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

	// Index ���� ����
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

	// �ν��Ͻ�
	CONTEXT->DrawIndexedInstanced(m_IdxCount, _iParticleCount, 0, 0, 0);
}

int CMesh::Load(const wstring& _strFilePath)
{
	// �б���� ���Ͽ���
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");
	if (nullptr != pFile)
	{
		// Ű��, �����
		wstring strName, strKey, strRelativePath;
		LoadWString(strName, pFile);
		LoadWString(strKey, pFile);
		LoadWString(strRelativePath, pFile);

		SetName(strName);
		SetKey(strKey);
		SetRelativePath(strRelativePath);

		// ����������
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

		// ����������
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
	// ����� ����
	SetRelativePath(_strRelativePath);

	// ���� ��� �����
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;

	path parentFolder(strFilePath);
	filesystem::create_directories(parentFolder.parent_path());

	// ���� ������� ����
	FILE* pFile = nullptr;
	errno_t err = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Ű��, ��� ���	
	SaveWString(GetName(), pFile);
	SaveWString(GetKey(), pFile);
	SaveWString(GetRelativePath(), pFile);

	// ���� ������ ����				
	int iByteSize = m_tVBDesc.ByteWidth;
	fwrite(&iByteSize, sizeof(int), 1, pFile);
	fwrite(m_pVtxSys, iByteSize, 1, pFile);

	// �ε��� ����
	iByteSize = m_tIBDesc.ByteWidth;
	fwrite(&iByteSize, sizeof(int), 1, pFile);
	fwrite(m_pIdxSys, iByteSize, 1, pFile);

	fclose(pFile);


	return S_OK;
	
}