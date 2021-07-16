#include "EditorLayer.h"
#include <imgui.h>

namespace Jass {

	EditorLayer::EditorLayer() :
		Layer("EditorLayer"), m_cameraController(1280.0f / 720.0f)
	{
	}

	void EditorLayer::OnAttach()
	{
		m_texture = Texture2D::Create("assets/textures/Checkerboard.png");

		m_scene = MakeRef<Scene>();
		m_sceneHierarchyPanel.SetContext(m_scene);
		m_propertiesPanel.SetContext(m_scene);

		// TEMPORARY
		m_squareEntity = m_scene->CreateEntity("Square");
		m_firstCamera = m_scene->CreateEntity("Camera A");
		m_secondCamera = m_scene->CreateEntity("Camera B");

		m_squareEntity.AddComponent<SpriteComponent>(JVec4{ 0.3f, 0.2f, 0.8f, 1.0f });

		m_firstCamera.AddComponent<CameraComponent>(MakeScope<OrthographicSceneCamera>(), true);
		
		m_secondCamera.AddComponent<CameraComponent>(MakeScope<OrthographicSceneCamera>(5.0f));
		m_secondCamera.GetComponent<TransformationComponent>().Position = JVec3(2.0f, 2.0f, 0.0f);

		FramebufferConfig fbConfig;
		fbConfig.Width = 1280;
		fbConfig.Height = 720;
		m_framebuffer = Framebuffer::Create(fbConfig);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		JASS_PROFILE_FUNCTION();

		// Resize
		auto fbConfig = m_framebuffer->GetConfig();
		if ((m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f) && // Only non-zero viewport is valid
			(fbConfig.Width != m_viewportSize.x || fbConfig.Height != m_viewportSize.y))
		{
			OnViewportResize((unsigned int)m_viewportSize.x, (unsigned int)m_viewportSize.y);
		}

		// Render
		Renderer2D::ResetStatistics();
		m_framebuffer->Bind();

		if (m_isViewportFocused)
			m_cameraController.OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
		RenderCommand::Clear();

		m_scene->OnUpdate(ts);
		
		m_framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		JASS_PROFILE_FUNCTION();

		static bool DockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &DockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                ImGui::Separator();
				if (ImGui::MenuItem("Exit"))	Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

		ShowDockableGUI();

        ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_cameraController.OnEvent(e);
	}

	void EditorLayer::ShowDockableGUI()
	{
		auto statistics = Renderer2D::GetStatistics();

		m_sceneHierarchyPanel.OnImGuiRender();
		m_propertiesPanel.OnImGuiRender();

		ImGui::Begin("Statistics");
		ImGui::Text("Total Draw Calls: %d", statistics.DrawCalls);
		ImGui::Text("Total Quads: %d", statistics.TotalQuads);
		ImGui::Text("Total Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Total Indices: %d", statistics.GetIndexCount());

		ImGui::Separator();
		ImGui::Text(m_squareEntity.GetComponent<TagComponent>().Tag.c_str());
		auto& squareColor = m_squareEntity.GetComponent<SpriteComponent>().Color;
		ImGui::ColorEdit4("Color", GetPtr(squareColor));

		if (ImGui::Checkbox("First camera", &m_firstCamera.GetComponent<CameraComponent>().Main)) {
			m_secondCamera.GetComponent<CameraComponent>().Main = !m_secondCamera.GetComponent<CameraComponent>().Main;
		}

		if (ImGui::Checkbox("Second camera", &m_secondCamera.GetComponent<CameraComponent>().Main)) {
			m_firstCamera.GetComponent<CameraComponent>().Main = !m_firstCamera.GetComponent<CameraComponent>().Main;
		}

		ImGui::Separator();

		ImGui::End();

		DrawViewport();
	}

	void EditorLayer::DrawViewport()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		auto viewportImgID = m_framebuffer->GetColorAttachmentRendererID();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		// Block events if the viewport is not focused and hovered
		m_isViewportFocused = ImGui::IsWindowFocused();
		bool isViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer().BlockEvents(!(m_isViewportFocused && isViewportHovered));

		ImGui::Image((ImTextureID)(uint64_t)viewportImgID,
			ImVec2{ m_viewportSize.x, m_viewportSize.y },
			ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::OnViewportResize(unsigned int width, unsigned int height)
	{
		m_framebuffer->Resize(width, height);
		m_scene->OnViewportResize(width, height);
		m_cameraController.OnResize(width, height);
	}

}