#include "jasspch.h"
#include "OrthographicSceneCamera.h"

#include "Jass/Camera/OrthographicCamera.h"

namespace Jass {

	OrthographicSceneCamera::OrthographicSceneCamera(float size, float aspectRatio, float nearPlane, float farPlane)
		:m_size(size)
	{
		m_aspectRatio = aspectRatio;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
	}

	Scope<Camera> OrthographicSceneCamera::GetCamera(const JVec3& position, const JVec3& rotation)
	{
		OrthographicCameraSettings settings;

		settings.Position = position;
		settings.Rotation = rotation;
		settings.Left = -m_size * m_aspectRatio * 0.5f;
		settings.Right = m_size * m_aspectRatio * 0.5f;
		settings.Bottom = -m_size * 0.5f;
		settings.Top = m_size * 0.5f;

		return MakeScope<OrthographicCamera>(settings);
	}

}
