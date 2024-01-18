#pragma once
#include "ResUI.h"

struct tModelNode;
class MeshUI;
class MaterialUI;
class ModelUI :
	public ResUI
{
private:
	MeshUI*			m_pMeshUI;
	MaterialUI*		m_pMaterialUI;
public:
	virtual int render_update() override;
private:
	void render_update_node(tModelNode* _pNode);
public:
	ModelUI();
	~ModelUI();
};

