#ifndef SCENE_H_JASS
#define SCENE_H_JASS

#include "Jass/Core/Timestep.h"
#include "entt.hpp"

namespace Jass {

	class Entity;

	class JASS_API Scene {

		friend class Entity;
		friend class SceneHierarchyPanel;

	public:
		Scene();

		void OnUpdate(Timestep ts);
		void OnViewportResize(unsigned int width, unsigned int height);

		Entity CreateEntity(const std::string& tag = std::string());

	private:
		entt::registry m_registry;

	};

}

#endif // !SCENE_H_JASS
