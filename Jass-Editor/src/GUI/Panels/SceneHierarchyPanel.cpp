#include "SceneHierarchyPanel.h"

#include <Jass/ECS/Components/Components.h>
#include <imgui.h>

namespace Jass {

	void SceneHierarchyPanel::OnImGuiRender()
	{
		if (!m_context)
			return;

		ImGui::Begin(m_name.c_str());

		m_context->m_registry.each([&](auto entity) {
			DrawEntityNode(entity);
		});

		// Unselect the entity when you click the panel
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) {
			s_storage.SelectedEntity = entt::null;
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(entt::entity entity)
	{
		auto& tag = m_context->m_registry.get<TagComponent>(entity).Tag;

		ImGuiTreeNodeFlags flags =
			((s_storage.SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow;

		// Begin a tree node using the entity id
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked()) {
			s_storage.SelectedEntity = entity;
		}

		if (opened) {
			// TODO: Render childs
			ImGui::TreePop();
		}
	}

}
