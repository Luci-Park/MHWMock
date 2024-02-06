#include "pch.h"
#include "ObjLayerInfoUI.h"
#pragma warning (disable:4996)

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>
#include <Engine\CLevel.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CEventMgr.h>



ObjLayerInfoUI::ObjLayerInfoUI()
	: ObjectInfoUI("##Obj_Layer", OBJINFO_TYPE::Obj_Layer)
	, items{}
	, item_current_idx(-1)
	, combo_preview_value(nullptr)
	, is_selected(false)
{
	SetName("Obj_Layer");

	int size = sizeof(LAYER_TYPE_STR) / sizeof(LAYER_TYPE_STR[0]);
	char cSubChar[] = "-";

	for (int i = 0; i < size; i++)
	{

		// LAYER_TYPE�� ������� ��� "-" �� �־���.
		if (LAYER_TYPE_STR[i] == "")
		{
			items[i] = new char[strlen(LAYER_TYPE_STR[i]) + 2];
			strcpy(const_cast<char*>(items[i]), cSubChar);
		}
		else
		{
			items[i] = new char[strlen(LAYER_TYPE_STR[i]) + 1];
			strcpy(const_cast<char*>(items[i]), LAYER_TYPE_STR[i]);
		}
	}
}


ObjLayerInfoUI::~ObjLayerInfoUI()
{
	for (int i = 0; i < MAX_LAYER; i++)
	{
		free(items[i]);
	}
}

int ObjLayerInfoUI::render_update()
{
	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	if (GetTarget()->IsDead())
		return FALSE;

	// Layer ComboBox.
	{
		item_current_idx = GetTarget()->GetLayerIndex(); 

		combo_preview_value = items[item_current_idx];  
		if (ImGui::BeginCombo("Layer", combo_preview_value, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				is_selected = (item_current_idx == n);
				if (ImGui::Selectable(items[n], is_selected))
				{
					item_current_idx = n;

					tEvent evn = {};
					evn.Type = EVENT_TYPE::LAYER_CHANGE;
					evn.wParam = (DWORD_PTR)GetTarget();
					evn.lParam = (DWORD_PTR)item_current_idx;
					CEventMgr::GetInst()->AddEvent(evn);
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	return TRUE;
}


