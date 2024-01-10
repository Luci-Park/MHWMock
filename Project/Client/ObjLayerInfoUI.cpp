#include "pch.h"
#include "ObjLayerInfoUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CLayer.h>

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

	//// Layer띄우기
	//int iLayerIdx = GetTarget()->GetLayerIndex();
	//string strLayerName = ToString((LAYER_TYPE)iLayerIdx);

	//char szBuff[50] = {};
	//strcpy(szBuff, strLayerName.c_str());
	//ImGui::Text("Layer		");
	//ImGui::SameLine();
	//ImGui::Text(szBuff);

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

		static int item_current_idx = 0; // Here we store our selection data as an index.
		const char* combo_preview_value = items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
		if (ImGui::BeginCombo("Layer", combo_preview_value, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(items[n], is_selected))
					item_current_idx = n;

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	return TRUE;
}


