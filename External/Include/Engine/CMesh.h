#pragma once
#include "CRes.h"

class aiMesh;
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

public:
	static CMesh* CreateFromAssimp(aiMesh* _aiMesh);
	void Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

private:
	virtual int Load(const wstring& _strFilePath);
public:
	virtual int Save(const wstring& _strRelativePath);


	void render();
	void render_particle(UINT _iParticleCount);



private:
	virtual void UpdateData() override;
	

public:
	CMesh(bool _bEngine = false);
	~CMesh();
};