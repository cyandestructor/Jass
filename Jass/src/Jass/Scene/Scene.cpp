#include "jasspch.h"
#include "Scene.h"

#include "Jass/ECS/Components/Components.h"
#include "Jass/ECS/Entity.h"
#include "Jass/Renderer/Renderer2D.h"

namespace Jass {

	Scene::Scene()
	{
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Get the main camera
		Scope<Camera> mainCamera = nullptr;
		{
			auto group = m_registry.group<CameraComponent>(entt::get<TransformationComponent>);

			for (auto entity : group) {
				auto& [camera, transformation] = group.get<CameraComponent, TransformationComponent>(entity);
				if (camera.Main) {
					mainCamera = camera.Camera->GetCamera(transformation.Position, transformation.Rotation);
					break;
				}
			}
		}
		
		if (mainCamera) {
			// Render 2D
			auto group = m_registry.group<TransformationComponent>(entt::get<SpriteComponent>);

			Renderer2D::BeginScene(*mainCamera);
			for (auto entity : group) {
				auto& [transformation, sprite] = group.get<TransformationComponent, SpriteComponent>(entity);
				Renderer2D::DrawQuad(transformation.GetTransformation(), sprite.Color);
			}
			Renderer2D::EndScene();
		}
	}

	Entity Scene::CreateEntity(const std::string& tag)
	{
		Entity entity = { m_registry.create(), this };
		// Every Entity has a transformation and tag by default
		entity.AddComponent<TransformationComponent>();
		entity.AddComponent<TagComponent>(tag.empty() ? "Entity" : tag);
		return entity;
	}

}
