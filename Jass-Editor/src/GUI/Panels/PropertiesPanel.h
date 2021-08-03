#ifndef PROPERTIES_PANEL_H
#define PROPERTIES_PANEL_H

#include "Panel.h"
#include "../ComponentDisplay/ComponentDisplay.h"

namespace Jass {

	class PropertiesPanel : public Panel {
	public:
		PropertiesPanel()
			: Panel("Properties") {}

		virtual void OnImGuiRender() override;

		void SetContext(const Ref<Scene>& context) { m_context = context; }

	private:
		Ref<Scene> m_context;

		template <typename Component>
		void DrawComponent(entt::entity entity);

		void DrawComponents(entt::entity entity);
	};

	template<typename Component>
	void PropertiesPanel::DrawComponent(entt::entity entity)
	{
		if (m_context->m_registry.all_of<Component>(entity)) {
			auto& c = m_context->m_registry.get<Component>(entity);
			ComponentDisplay::Display<Component>(c);
		}
	}

}

#endif // !PROPERTIES_PANEL_H
