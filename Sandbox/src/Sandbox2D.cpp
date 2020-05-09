#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D"), 
	m_CameraController(1280.0f / 720.0f, true), 
	m_TilingFactor(1.0f),
	m_Rotation(0.0f),
	m_FirstColor(0.2f, 0.3f, 0.8f, 1.0f), 
	m_SecondColor(0.8f, 0.2f, 0.3f, 1.0f)
{

}


void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}


void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	//Timer timer("Sandbox:OnUpdate");

	// UPDATE

	m_CameraController.OnUpdate(ts);


	// RENDER

	Hazel::Renderer2D::ResetStats();

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.5f }, { 0.8f, 0.8f }, m_Rotation, m_SecondColor);
	Hazel::Renderer2D::DrawQuad({ -0.5f, 0.5f, 1.0f }, { 0.8f, 0.8f }, m_SecondColor);
	Hazel::Renderer2D::DrawQuad({ 0.25f, -0.25f }, { 1.2f, 1.2f }, m_FirstColor);
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, m_TilingFactor, {1.0f, 1.0f, 1.0f, 1.0f});
	Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }, m_Rotation, m_Texture, 0.5f);

	//Hazel::Renderer2D::EndScene();
	//Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x= -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 1.0f, 0.5f };
			Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}

	Hazel::Renderer2D::EndScene();

}



void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::DragFloat("Tiling factor", &m_TilingFactor, 0.1f, 0.1f, 10.0f);
	ImGui::DragFloat("Rotation", &m_Rotation, 0.1f);
	ImGui::ColorEdit4("First Color", glm::value_ptr(m_FirstColor));
	ImGui::ColorEdit4("Second Color", glm::value_ptr(m_SecondColor));
	ImGui::End();


	auto stats = Hazel::Renderer2D::GetStats();
	
	ImGui::Begin("Stats");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();

	//ImGui::ShowDemoWindow();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}