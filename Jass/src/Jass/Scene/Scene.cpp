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
		m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
			// TODO: Move to OnScenePlay
			if (!nsc.Instance) {
				nsc.Instance = nsc.Instantiate();
				nsc.Instance->m_entity = Entity(entity, this);
				nsc.Instance->OnCreate();
			}

			nsc.Instance->OnUpdate(ts);
			// TODO: Call OnDestroy and Destroy for scripts when Scene stops
		});

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

	void Scene::OnViewportResize(unsigned int width, unsigned int height)
	{
		auto view = m_registry.view<CameraComponent>();

		for (auto entity : view) {
			auto& camera = view.get<CameraComponent>(entity);
			if (!camera.FixedAspectRatio) {
				camera.Camera->SetViewportSize(width, height);
			}
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
