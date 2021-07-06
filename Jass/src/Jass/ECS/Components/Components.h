#ifndef COMPONENTS_H_JASS
#define COMPONENTS_H_JASS

#include "Jass/JMath/JMath.h"
#include "Jass/Scene/OrthographicSceneCamera.h"

namespace Jass {

	struct TransformationComponent
	{
		TransformationComponent() = default;
		TransformationComponent(const TransformationComponent& other) = default;

		JVec3 Position = JVec3(0.0f);
		JVec3 Rotation = JVec3(0.0f);
		JVec3 Scale = JVec3(1.0f);
		
		JMat4 GetTransformation() const
		{
			JMat4 transformation = Translate(JMat4(1.0f), Position);
			transformation = Rotate(transformation, Radians(Rotation.x), JVec3(-1.0f, 0.0f, 0.0f));
			transformation = Rotate(transformation, Radians(Rotation.y), JVec3(0.0f, -1.0f, 0.0f));
			transformation = Rotate(transformation, Radians(Rotation.z), JVec3(0.0f, 0.0f, -1.0f));
			transformation = Jass::Scale(transformation, Scale);
			return transformation;
		}
	};

	struct CameraComponent
	{
		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(CameraComponent&& other) = default;
		CameraComponent& operator=(const CameraComponent& other) = default;
		CameraComponent& operator=(CameraComponent&& other) = default;
		CameraComponent(Scope<SceneCamera> camera, bool main = false)
			: Camera(std::move(camera)), Main(main) {}

		Scope<SceneCamera> Camera = nullptr;
		bool Main = false;
	};

	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = default;
		SpriteComponent(const JVec4 & color) :
			Color(color) {}

		JVec4 Color = JVec4(1.0f);
	};

	struct TagComponent
	{
		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag) :
			Tag(tag) {}

		std::string Tag;
	};

}

#endif // !COMPONENTS_H_JASS
