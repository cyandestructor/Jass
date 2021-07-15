#ifndef SCENE_HIERARCHY_PANEL_H
#define SCENE_HIERARCHY_PANEL_H

#include "Panel.h"

namespace Jass {

	class SceneHierarchyPanel : public Panel {
	public:
		SceneHierarchyPanel()
			: Panel("Scene Hierarchy") {}

		virtual void OnImGuiRender() override;

		void SetContext(const Ref<Scene>& context) { m_context = context; }

	private:
		Ref<Scene> m_context;

		void DrawEntityNode(entt::entity entity);
	};

}

#endif // !SCENE_HIERARCHY_PANEL_H
