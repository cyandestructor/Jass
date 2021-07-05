#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include "Jass/Core/Core.h"
#include "Jass/JMath/JMath.h"
#include "Jass/Camera/Camera.h"

namespace Jass {

	class SceneCamera {
	public:
		virtual ~SceneCamera() = default;

		virtual Scope<Camera> GetCamera(const JVec3& position, const JVec3& rotation) = 0;
		
		void SetViewportSize(unsigned int width, unsigned int height) {
			m_aspectRatio = (float)width / (float)height;
		}

	protected:
		float m_aspectRatio = 1.0f;
		float m_nearPlane = -1.0f;
		float m_farPlane = 1.0f;

	};

}

#endif // !SCENE_CAMERA_H

