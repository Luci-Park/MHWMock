#include "pch.h"
#include "ObjLayerInfoUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>
#include <Engine\CLevel.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CEventMgr.h>



ObjLayerInfoUI::ObjLayerInfoUI()
	: ObjectInfoUI("##Obj_Layer", OBJINFO_TYPE::Obj_Layer)
{
	SetName("Obj_Layer");
}


ObjLayerInfoUI::~ObjLayerInfoUI()
{
}
int ObjLayerInfoUI::render_update()
{
	if (FALSE == ObjectInfoUI::render_update())
		return FALSE;

	// Layer ComboBox.
	{
		const char* items[MAX_LAYER] = {0};
		const int size = sizeof(LAYER_TYPE_STR) / sizeof(LAYER_TYPE_STR[0]);
		
		for (int i = 0; i < size; i++)
		{
			items[i] = new char[strlen(LAYER_TYPE_STR[i]) + 1];

			// LAYER_TYPE이 비어있을 경우 "-" 를 넣어줌.
			if (LAYER_TYPE_STR[i] == "")
			{
				strcpy(const_cast<char*>(items[i]), "-");
			}
			else
			{
				strcpy(const_cast<char*>(items[i]), LAYER_TYPE_STR[i]);
			}
		}

		int item_current_idx = GetTarget()->GetLayerIndex(); 

		const char* combo_preview_value = items[item_current_idx];  
		if (ImGui::BeginCombo("Layer", combo_preview_value, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				const bool is_selected = (item_current_idx == n);
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


