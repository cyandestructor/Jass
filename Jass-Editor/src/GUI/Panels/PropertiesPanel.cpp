#include "PropertiesPanel.h"

#include "../ComponentDisplay/ComponentDisplay.h"

namespace Jass {

	void PropertiesPanel::OnImGuiRender()
	{
		if (!m_context)
			return;

		ImGui::Begin(m_name.c_str());
		
		if (s_storage.SelectedEntity == entt::null) {
			ImGui::Text("No selection");
		}
		else {
			DrawComponents(s_storage.SelectedEntity);
		}

		ImGui::End();
	}

	void PropertiesPanel::DrawComponents(entt::entity entity)
	{
		if (m_context->m_registry.all_of<TagComponent>(entity)) {
			auto& tc = m_context->m_registry.get<TagComponent>(entity);
			ComponentDisplay::Display<TagComponent>(tc);
		}
	}

}