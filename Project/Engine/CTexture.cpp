#include "pch.h"
#include "CTexture.h"

#include "CDevice.h"
#include "CPathMgr.h"

CTexture::CTexture(bool _bEngine)
	: CRes(RES_TYPE::TEXTURE, _bEngine)
	, m_Desc{}
{
}

CTexture::~CTexture()
{
}


void CTexture::UpdateData(int _iRegisterNum, int _PipelineStage)
{
	m_iRecentNum = _iRegisterNum;

	if (PIPELINE_STAGE::PS_VERTEX & _PipelineStage)
	{
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_HULL & _PipelineStage)
	{
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_DOMAIN & _PipelineStage)
	{
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_GEOMETRY & _PipelineStage)
	{
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_PIXEL & _PipelineStage)
	{
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
}

void CTexture::UpdateData_CS(int _iRegisterNum, bool _bShaderRes)
{
	m_iRecentNum = _iRegisterNum;

	if (_bShaderRes)
	{
		CONTEXT->CSSetShaderResources(m_iRecentNum, 1, m_SRV.GetAddressOf());
	}
	else
	{
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_iRecentNum, 1, m_UAV.GetAddressOf(), &i);
	}
}

void CTexture::Clear()
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	CONTEXT->VSSetShaderResources(m_iRecentNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(m_iRecentNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(m_iRecentNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(m_iRecentNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(m_iRecentNum, 1, &pSRV);
}

void CTexture::Clear(int _iRegisterNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	CONTEXT->VSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, &pSRV);
}

void CTexture::Clear_CS(bool _bShaderRes)
{
	if (_bShaderRes)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		CONTEXT->CSSetShaderResources(m_iRecentNum, 1, &pSRV);
	}
	else
	{
		ID3D11UnorderedAccessView* pUAV = nullptr;
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_iRecentNum, 1, &pUAV, &i);
	}
}

void CTexture::UpdateData()
{
}


int CTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[50] = L"";
	wchar_t szFileName[512] = L"";
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, szFileName, 512, szExt, 50);
	wstring strExt = szExt;
	wstring strFileName = szFileName;

	HRESULT hr = S_OK;
	if (L".dds" == strExt || L".DDS" == strExt)
	{
		// dds, DDS
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
	}

	else if (L".tga" == strExt || L".TGA" == strExt)
	{
		// tga, TGA
		hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);
	}

	else
	{
		// png, jpg, jpeg, bmp
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
	}
	
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"리소스 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	hr = CreateShaderResourceView(DEVICE
		, m_Image.GetImages()
		, m_Image.GetImageCount()
		, m_Image.GetMetadata()
		, m_SRV.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShaderResourceView 생성 실패", L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());
	m_Tex2D->GetDesc(&m_Desc);

	SetName(strFileName);

	return S_OK;
}

int CTexture::Create(UINT _Width, UINT _Height, DXGI_FORMAT _pixelformat
	, UINT _BindFlag, D3D11_USAGE _Usage)
{
	// ID3D11Texture2D 생성
	m_Desc.Format = _pixelformat;

	// 반드시 렌더타겟과 같은 해상도로 설정해야 함
	m_Desc.Width = _Width;
	m_Desc.Height = _Height;
	m_Desc.ArraySize = 1;

	m_Desc.BindFlags = _BindFlag;
	m_Desc.Usage = _Usage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _Usage)
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	else if(D3D11_USAGE::D3D11_USAGE_STAGING == _Usage)
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	m_Desc.MipLevels = 1;    // 원본만 생성
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;


	if (FAILED(DEVICE->CreateTexture2D(&m_Desc, nullptr, m_Tex2D.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 바인드 플래그에 맞는 View 를 생성해준다.
	if (m_Desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		if (FAILED(DEVICE->CreateDepthStencilView(m_Tex2D.Get(), nullptr, m_DSV.GetAddressOf())))
		{
			return E_FAIL;
		}
	}
	else
	{
		if (m_Desc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			if (FAILED(DEVICE->CreateRenderTargetView(m_Tex2D.Get(), nullptr, m_RTV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			if (FAILED(DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			if (FAILED(DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}
	}


	return S_OK;
}

int CTexture::Create(ComPtr<ID3D11Texture2D> _tex2D)
{
	m_Tex2D = _tex2D;

	m_Tex2D->GetDesc(&m_Desc);

	// 바인드 플래그에 맞는 View 를 생성해준다.
	if (m_Desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		if (FAILED(DEVICE->CreateDepthStencilView(m_Tex2D.Get(), nullptr, m_DSV.GetAddressOf())))
		{
			return E_FAIL;
		}
	}
	else
	{
		if (m_Desc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			if (FAILED(DEVICE->CreateRenderTargetView(m_Tex2D.Get(), nullptr, m_RTV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			if (FAILED(DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}

		if (m_Desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		{
			if (FAILED(DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf())))
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

int CTexture::CreateArrayTexture(const vector<Ptr<CTexture>>& _vecTex, int _iMapLevel)
{
	m_Desc = _vecTex[0]->GetDesc();
	m_Desc.ArraySize = (UINT)_vecTex.size();
	m_Desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_Desc.MipLevels = _iMapLevel;

	HRESULT hr = DEVICE->CreateTexture2D(&m_Desc, nullptr, m_Tex2D.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// 원본데이터(밉맵 레벨 0) 를 각 칸에 옮긴다.	
	for (int i = 0; i < _vecTex.size(); ++i)
	{
		UINT iOffset = D3D11CalcSubresource(0, i, _iMapLevel);
		CONTEXT->UpdateSubresource(m_Tex2D.Get(), iOffset, nullptr, _vecTex[i]->GetSysMem()
			, _vecTex[i]->GetRowPitch(), _vecTex[i]->GetSlicePitch());
	}

	// Shader Resource View 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC viewdesc = {};
	viewdesc.Format = m_Desc.Format;
	viewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	viewdesc.Texture2DArray.MipLevels = _iMapLevel;
	viewdesc.Texture2DArray.MostDetailedMip = 0;
	viewdesc.Texture2DArray.ArraySize = _vecTex.size();

	DEVICE->CreateShaderResourceView(m_Tex2D.Get(), &viewdesc, m_SRV.GetAddressOf());

	// 밉맵 생성
	CONTEXT->GenerateMips(m_SRV.Get());
	m_Tex2D->GetDesc(&m_Desc);

	return hr;
	return 0;
}


void CTexture::GenerateMip(UINT _iMipLevel)
{
	m_Tex2D = nullptr;
	m_SRV = nullptr;
	m_RTV = nullptr;
	m_DSV = nullptr;
	m_UAV = nullptr;

	// Texture2D 생성
	D3D11_TEXTURE2D_DESC tDesc = {};
	tDesc.Format = m_Image.GetMetadata().format;

	if (m_Image.GetMetadata().IsCubemap())
	{
		tDesc.MipLevels = 1;	// 0 ==> 가능한 모든 밉맵이 저장 될 수 있는 공간이 만들어짐
		tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		tDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}
	else
	{
		tDesc.MipLevels = _iMipLevel;// MAX_MIP;	// 0 ==> 가능한 모든 밉맵이 저장 될 수 있는 공간이 만들어짐	
		tDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		tDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	tDesc.ArraySize = m_Image.GetMetadata().arraySize;

	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.CPUAccessFlags = 0;

	tDesc.Width = m_Image.GetMetadata().width;
	tDesc.Height = m_Image.GetMetadata().height;

	HRESULT hr = DEVICE->CreateTexture2D(&tDesc, nullptr, m_Tex2D.GetAddressOf());

	// 원본데이터(밉맵 레벨 0) 를 각 칸에 옮긴다.	
	for (int i = 0; i < tDesc.ArraySize; ++i)
	{
		// GPU 에 데이터 옮기기(밉맵 포함)
		UINT iSubresIdx = D3D11CalcSubresource(0, i, tDesc.MipLevels);

		CONTEXT->UpdateSubresource(m_Tex2D.Get(), iSubresIdx, nullptr
			, m_Image.GetImage(0, i, 0)->pixels
			, m_Image.GetImage(0, i, 0)->rowPitch
			, m_Image.GetImage(0, i, 0)->slicePitch);
	}

	// SRV 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC viewdesc = {};
	viewdesc.Format = tDesc.Format;

	if (m_Image.GetMetadata().IsCubemap())
	{
		viewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	}
	else if (1 < tDesc.ArraySize)
	{
		viewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	}
	else
	{
		viewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	}

	if (1 < tDesc.ArraySize)
	{
		viewdesc.Texture2DArray.ArraySize = tDesc.ArraySize;
		viewdesc.Texture2DArray.MipLevels = tDesc.MipLevels;
		viewdesc.Texture2DArray.MostDetailedMip = 0;
	}
	else
	{
		viewdesc.Texture2DArray.ArraySize = 1;
		viewdesc.Texture2D.MipLevels = tDesc.MipLevels;
		viewdesc.Texture2D.MostDetailedMip = 0;
	}

	DEVICE->CreateShaderResourceView(m_Tex2D.Get(), &viewdesc, m_SRV.GetAddressOf());

	// 밉맵 생성
	if (false == m_Image.GetMetadata().IsCubemap())
	{
		CONTEXT->GenerateMips(m_SRV.Get());
	}

	m_Tex2D->GetDesc(&m_Desc);
}






int CTexture::Save(const wstring& _strRelativePath)
{
	return S_OK;
}