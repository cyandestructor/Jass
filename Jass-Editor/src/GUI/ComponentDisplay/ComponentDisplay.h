#ifndef COMPONENT_DISPLAY_H
#define COMPONENT_DISPLAY_H

#include <Jass/ECS/Components/Components.h>
#include <imgui.h>

namespace Jass {

	namespace ComponentDisplay {

		template <typename Component>
		void Display(Component& component)
		{
			static_assert(false, "Function Display() for this component is not defined");
		}

		template <>
		void Display(TagComponent& component);

		template <>
		void Display(TransformationComponent& component);
	}

}

#endif // !COMPONENT_DISPLAY_H
