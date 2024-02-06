#include "pch.h"
#include "UI.h"
#include <Engine\CGameObject.h>

UI::UI(const string& _ID)
	: m_strID(_ID)
	, m_ParentUI(nullptr)
	, m_Modal(false)
	, m_Active(false)
	, m_bUseSeparator(true)
{
	
}

UI::~UI()
{
	Safe_Del_Vec(m_vecChildUI);
}

void UI::finaltick()
{	
	if (!m_Active)
		return;

	string strFullName = m_strName + m_strID;

	// �θ� UI
	if (nullptr == m_ParentUI)
	{
		// ��޸���
		if (!m_Modal)
		{
			ImGui::Begin(strFullName.c_str(), &m_Active);

			render_update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				// �ڽ�UI �� ��Ȱ��ȭ ���¸� �ǳʶڴ�.
				if (!m_vecChildUI[i]->IsActive())
					continue;

				m_vecChildUI[i]->finaltick();


				if (m_vecChildUI[i]->m_bUseSeparator)
				{
					// �ڽ� UI ���� ���м�
					if (i != m_vecChildUI.size() - 1)
						ImGui::Separator();
				}
			}

				if (m_vecChildUI[i]->m_bUseSeparator)
				{
					// �ڽ� UI ���� ���м�
					if (i != m_vecChildUI.size() - 1)
						ImGui::Separator();
				}
			}
			ImGui::End();
		}

		// ���
		else
		{
			ImGui::SetNextWindowPos(m_vPopupPos);
			ImGui::SetNextWindowSize(m_vSize);

			ImGui::OpenPopup(strFullName.c_str());
			if (ImGui::BeginPopupModal(strFullName.c_str(), &m_Active))
			{
				render_update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					// �ڽ�UI �� ��Ȱ��ȭ ���¸� �ǳʶڴ�.
					if (!m_vecChildUI[i]->IsActive())
						continue;

					m_vecChildUI[i]->finaltick();

					if (m_vecChildUI[i]->m_bUseSeparator)
					{
						// �ڽ� UI ���� ���м�
						if (i != m_vecChildUI.size() - 1)
							ImGui::Separator();
					}
				}

				ImGui::EndPopup();
			}
		}
	}

	// �ڽ� UI
	else
	{
		ImGui::BeginChild(strFullName.c_str(), m_vSize);

		
		render_update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->finaltick();

			if (m_vecChildUI[i]->m_bUseSeparator)
			{	
				// �ڽ� UI ���� ���м�
				if (i != m_vecChildUI.size() - 1)
					ImGui::Separator();
			}
		}

		ImGui::EndChild();
	}
}