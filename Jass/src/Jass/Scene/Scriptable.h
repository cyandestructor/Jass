#ifndef SCRIPTABLE_H
#define SCRIPTABLE_H

#include "Jass/ECS/Entity.h"

namespace Jass {

	class Scriptable {
		friend class Scene;
	public:
		virtual ~Scriptable() = default;

		template <typename Component>
		Component& GetComponent() {
			return m_entity.GetComponent<Component>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}

	private:
		Entity m_entity;
	};

}

#endif // !SCRIPTABLE_H
