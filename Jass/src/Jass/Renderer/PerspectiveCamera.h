#ifndef PERSPECTIVE_CAMERA_H_JASS
#define PERSPECTIVE_CAMERA_H_

#include "Camera.h"

namespace Jass {

	struct JASS_API PerspectiveCameraSettings {
		glm::vec3 Position;
		glm::vec3 Rotation;
		float FOV;
		float ViewportWidth;
		float ViewportHeight;
		float Near;
		float Far;

		PerspectiveCameraSettings() :
			Position({ 0.0f,0.0f,0.0f }), Rotation({ 0.0f,0.0f,0.0f }),
			FOV(60.0f), ViewportWidth(1280.0f), ViewportHeight(720.0f), Near(0.1f), Far(100.0f) {}
	};

	class JASS_API PerspectiveCamera : public Camera {

	public:
		PerspectiveCamera(const PerspectiveCameraSettings& settings);

		virtual void SetPosition(const glm::vec3& position) override;
		virtual void SetRotation(const glm::vec3& rotation) override;

		inline const PerspectiveCameraSettings& GetSettings() const { return m_settings; }

		inline virtual const glm::vec3& GetPosition() const override { return m_settings.Position; }
		inline virtual const glm::vec3& GetRotation() const override { return m_settings.Rotation; }

	private:
		PerspectiveCameraSettings m_settings;

		void CalculateMatrices();

	};

}

#endif // !PERSPECTIVE_CAMERA_H_JASS