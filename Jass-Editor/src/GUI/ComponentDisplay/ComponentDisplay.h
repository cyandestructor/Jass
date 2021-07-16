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
		void Display(TagComponent& component)
		{
			std::array<char, 256> buffer;
			buffer.fill(0);
			strcpy_s(buffer.data(), sizeof(buffer), component.Tag.c_str());
			if (ImGui::InputText("Tag", buffer.data(), sizeof(buffer)))
			{
				component.Tag = std::string(buffer.data());
			}
		}

	}

}

#endif // !COMPONENT_DISPLAY_H
