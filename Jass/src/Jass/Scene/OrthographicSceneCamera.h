#ifndef ORTHOGRAPHIC_SCENE_CAMERA_H
#define ORTHOGRAPHIC_SCENE_CAMERA_H

#include "Jass/Scene/SceneCamera.h"

namespace Jass {

	class OrthographicSceneCamera : public SceneCamera {
	public:
		OrthographicSceneCamera() = default;
		OrthographicSceneCamera(float size, float aspectRatio, float nearPlane, float farPlane);

		virtual ~OrthographicSceneCamera() = default;

		virtual Scope<Camera> GetCamera(const JVec3& position, const JVec3& rotation) override;

	private:
		float m_size = 10.0f;

	};

}

#endif // !ORTHOGRAPHIC_SCENE_CAMERA_H

