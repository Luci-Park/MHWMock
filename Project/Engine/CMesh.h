#pragma once
#include "CRes.h"

class CStructuredBuffer;
class aiMesh;
class CModel;
class CMesh
	: public CRes
{
private:
	ComPtr<ID3D11Buffer>	m_VB;
	D3D11_BUFFER_DESC		m_tVBDesc;
	UINT					m_VtxCount;
	void*					m_pVtxSys;

	ComPtr<ID3D11Buffer>	m_IB;
	D3D11_BUFFER_DESC		m_tIBDesc;
	UINT					m_IdxCount;
	void*					m_pIdxSys;

	vector<Vec3>			m_vecVertices;
	vector<wstring>			m_vecBones;
	CStructuredBuffer*		m_pBoneOffset;


public:
	static CMesh* CreateFromAssimp(aiMesh* _aiMesh, CModel* _pModel);
	void Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);
	vector<wstring>& GetBoneNames() { return m_vecBones; }
	int GetNumberOfBones() { return m_vecBones.size(); }
	bool HasBones() { return m_vecBones.size() != 0; }

	void* GetVtxSys() { return m_pVtxSys; }
	void* GetIdxSys() { return m_pIdxSys; }
	UINT	GetVtxCount() {return m_VtxCount;}
	UINT	GetVIdxCount() {return m_IdxCount;}

public:
	virtual int Save(const wstring& _strRelativePath) override;
	virtual int Load(const wstring& _strFilePath) override;


	void render();
	void render_particle(UINT _iParticleCount);



private:
	virtual void UpdateData() override;


public:
	CMesh(bool _bEngine = false);
	~CMesh();
};