#include "PropertiesPanel.h"

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
		DrawComponent<TagComponent>(entity);
		
		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
		if (ImGui::TreeNodeEx((void*)typeid(TransformationComponent).hash_code(), flags, "Transformation"))
		{
			DrawComponent<TransformationComponent>(entity);
			ImGui::TreePop();
		}

	}

}