#ifndef ENTITY_H_JASS
#define ENTITY_H_JASS

#include "Jass/Scene/Scene.h"
#include "Jass/ECS/Components/NativeScriptComponent.h"

namespace Jass {

	class JASS_API Entity {
		friend class Scene;

	public:
		Entity() = default;
		Entity(const Entity&) = default;

		template<typename Component>
		bool HasComponent() const
		{
			return m_scene->m_registry.has<Component>(m_handler);
		}

		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			JASS_CORE_ASSERT(!HasComponent<Component>(), "Entity already has that component");
			
			return m_scene->m_registry.emplace<Component>(m_handler, std::forward<Args>(args)...);
		}

		template<typename Component>
		Component& GetComponent()
		{
			JASS_CORE_ASSERT(HasComponent<Component>(), "Entity does not have that component");

			return m_scene->m_registry.get<Component>(m_handler);
		}

		template<typename Component>
		void RemoveComponent()
		{
			JASS_CORE_ASSERT(HasComponent<Component>(), "Entity does not have that component");
			
			m_scene->m_registry.remove<Component>(m_handler);
		}

		template<typename T>
		void AddNativeScript()
		{
			if (!HasComponent<NativeScriptComponent>())
				m_scene->m_registry.emplace<NativeScriptComponent>(m_handler);

			auto& nsc = m_scene->m_registry.get<NativeScriptComponent>(m_handler);
			auto& script = nsc.NativeScripts.emplace_back();
			
			// Set Instantiate and Destroy functions to be called on Scene play
			script.Instantiate = []() { return static_cast<Scriptable*>(new T()); };
			script.Destroy = [](NativeScriptComponent::NativeScript& ns) {
				delete ns.Instance;
				ns.Instance = nullptr;
			};
		}

		operator bool() const { return m_handler != entt::null; }

	private:
		entt::entity m_handler = entt::null;
		Scene* m_scene = nullptr;

		Entity(entt::entity handler, Scene* scene);

	};

}

#endif // !ENTITY_H_JASS
