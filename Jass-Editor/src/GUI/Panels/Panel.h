#ifndef PANEL_H
#define PANEL_H

#include <Jass/Scene/Scene.h>

namespace Jass {

	class Panel {
	public:
		Panel(const std::string& name)
			: m_name(name) {}

		virtual ~Panel() = default;

		virtual void OnImGuiRender() = 0;

	protected:
		static struct Storage {
			entt::entity SelectedEntity = entt::null;
		} s_storage;

		std::string m_name;
	};

}

#endif // !PANEL_H
