#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_texture = Jass::Texture2D::Create("assets/textures/Checkerboard.png");

	m_tileMap = Jass::Texture2D::Create("assets/textures/Tilemap/tilemap_packed.png");
	m_tileCar = Jass::SubTexture2D::Create(m_tileMap, { 15.0f * 16.0f, 0.0f }, { 32.0f, 32.0f });
	m_tileTaxi = Jass::SubTexture2D::Create(m_tileMap, { 15.0f * 16.0f, 2.0f * 16.0f }, { 32.0f, 32.0f });
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Jass::Timestep ts)
{
	JASS_PROFILE_FUNCTION();

	Jass::Renderer2D::ResetStatistics();

	m_cameraController.OnUpdate(ts);

	Jass::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.0f });
	Jass::RenderCommand::Clear();

	Jass::Renderer2D::BeginScene(m_cameraController.GetCamera());
	//DrawQuadsTest(ts);	// Uncomment to show multi-quad test
	DrawSpritesTest(ts);
	Jass::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	JASS_PROFILE_FUNCTION();

	auto statistics = Jass::Renderer2D::GetStatistics();

	ImGui::Begin("Statistics");
	ImGui::Text("Total Draw Calls: %d", statistics.DrawCalls);
	ImGui::Text("Total Quads: %d", statistics.TotalQuads);
	ImGui::Text("Total Vertices: %d", statistics.GetVertexCount());
	ImGui::Text("Total Indices: %d", statistics.GetIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(Jass::Event& e)
{
	m_cameraController.OnEvent(e);
}

void Sandbox2D::DrawQuadsTest(Jass::Timestep ts)
{
	static float rotation = 0.0f;
	rotation += 30.0f * ts;
	rotation = rotation > 360.0f ? rotation - 360.0f : rotation;

	Jass::Renderer2D::DrawQuad({ 0.5f, 0.75f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.25f, -0.5f }, { 0.25f, 0.5f }, { 0.3f, 0.2f, 0.8f, 1.0f });
	Jass::Renderer2D::DrawRotatedQuad({ 1.0f, -0.75f }, Jass::Radians(rotation), { 1.1f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Jass::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_texture, 10.0f);

	Jass::JVec4 color = { 1.0f, 0.5f, 1.0f, 1.0f };
	for (float x = -5.0f; x < 5.0f; x += 0.5f) {
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			color.r = (x + 5.0f) / 10.0f;
			color.b = (y + 5.0f) / 10.0f;
			Jass::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
}

void Sandbox2D::DrawSpritesTest(Jass::Timestep ts)
{
	Jass::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_tileCar);
	Jass::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_tileTaxi);
}
