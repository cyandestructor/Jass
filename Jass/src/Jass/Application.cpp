#include "jasspch.h"
#include "Application.h"

#include "Jass/Events/EventDispatcher.h"

// TEMPORARY
#include <glad/glad.h>

namespace Jass {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		JASS_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;
		m_window = std::unique_ptr<IWindow>(IWindow::Create());
		m_window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_imGuiLayer = new ImGuiLayer();
		PushOverlay(m_imGuiLayer);

		// TEMPORARY
		RendererAPITest();

	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		JASS_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend();) {
			// Pass the event though the layers
			(*it++)->OnEvent(e);
			// Stop when the event has been handled
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer->OnAttach();
		m_layerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		while (m_isRunning) {

			glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// TEMPORARY

			m_shader->Bind();
			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			//--------------

			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_imGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_imGuiLayer->End();

			m_window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

	void Application::RendererAPITest()
	{
		float positions[]{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.4f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.1f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.2f, 0.5f, 0.5f, 1.0f
		};

		unsigned int indices[]{
			0, 1, 2
		};

		std::string vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec4 position;
			layout(location = 1) in vec4 v_color;
	
			out vec4 color;			

			void main()
			{
				gl_Position = position;
				color = v_color;
			}
			
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_color;
				
			in vec4 color;

			void main()
			{
				o_color = color;
			}
			
		)";

		m_shader = std::make_shared<Shader>(vertexShader, fragmentShader);

		m_vertexArray.reset(VertexArray::Create());

		m_vertexBuffer.reset(VertexBuffer::Create({ positions,21 * sizeof(float),DataUsage::StaticDraw }));

		BufferLayout layout = {
			{ShaderDataType::Float3, "position" },
			{ShaderDataType::Float4, "v_color"}
		};
		m_vertexBuffer->SetLayout(layout);

		m_vertexArray->AddVertexBuffer(m_vertexBuffer);

		m_indexBuffer.reset(IndexBuffer::Create({ indices,3,DataUsage::StaticDraw }));

		m_vertexArray->SetIndexBuffer(m_indexBuffer);
	}

}
