#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include <Jass.h>
#include "GUI/Panels/SceneHierarchyPanel.h"
#include "GUI/Panels/PropertiesPanel.h"

namespace Jass {

	class EditorLayer : public Layer {

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_cameraController;

		Ref<Texture2D> m_texture;

		Ref<Scene> m_scene;
		Entity m_squareEntity;
		Entity m_firstCamera;
		Entity m_secondCamera;

		Ref<Framebuffer> m_framebuffer;

		SceneHierarchyPanel m_sceneHierarchyPanel;
		PropertiesPanel m_propertiesPanel;

		bool m_isViewportFocused = false;
		JVec2 m_viewportSize = JVec2(0.0f);

		void ShowDockableGUI();

		void DrawViewport();
		void OnViewportResize(unsigned int width, unsigned int height);

	};

}

#endif // !EDITOR_LAYER_H
