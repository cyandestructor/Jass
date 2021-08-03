#include "jasspch.h"
#include "ComponentDisplay.h"

namespace Jass {

	namespace ComponentDisplay {

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

		template <>
		void Display(TransformationComponent& component)
		{
			auto& position = component.Position;
			auto& rotation = component.Rotation;
			auto& scale = component.Scale;

			const float SPEED = 0.1f;

			ImGui::DragFloat3("Position", GetPtr(position), SPEED);
			ImGui::DragFloat3("Rotation", GetPtr(rotation), SPEED);
			ImGui::DragFloat3("Scale", GetPtr(scale), SPEED);
		}

	}

}