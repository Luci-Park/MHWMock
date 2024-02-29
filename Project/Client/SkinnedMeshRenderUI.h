#pragma once
#include "ComponentUI.h"

class SkinnedMeshRenderUI :
	public ComponentUI
{
private:
	UINT m_Idx;
public:
	virtual int render_update() override;
public:
	void SelectMesh(DWORD_PTR _Key);
	void SelectMaterial(DWORD_PTR _Key);
	void SelectTexture(DWORD_PTR _Key);

public:
	SkinnedMeshRenderUI();
	~SkinnedMeshRenderUI();
};

