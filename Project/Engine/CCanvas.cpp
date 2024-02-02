#include "pch.h"
#include "CCanvas.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"

CCanvas::CCanvas()
	:CComponent(COMPONENT_TYPE::CANVAS)
{

}

CCanvas::~CCanvas()
{

}

void CCanvas::tick()
{

}

void CCanvas::finaltick()
{

}

void CCanvas::sortCanvasObj()
{
	CLevel* level = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* layer = level->GetLayer((int)LAYER_TYPE::ViewPortUI);
	const vector<CGameObject*>& vecObject = layer->GetObjects();
	for (size_t i = 0; i < vecObject.size(); i++)
	{

	}
}