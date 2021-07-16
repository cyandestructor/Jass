#ifndef PROPERTIES_PANEL_H
#define PROPERTIES_PANEL_H

#include "Panel.h"

namespace Jass {

	class PropertiesPanel : public Panel {
	public:
		PropertiesPanel()
			: Panel("Properties") {}

		virtual void OnImGuiRender() override;

		void SetContext(const Ref<Scene>& context) { m_context = context; }

	private:
		Ref<Scene> m_context;

		void DrawComponents(entt::entity entity);
	};

}

#endif // !PROPERTIES_PANEL_H
