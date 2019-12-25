#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D"), m_CameraController(1280.0f / 720.0f, true), m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
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
	// UPDATE

	m_CameraController.OnUpdate(ts);


	// RENDER

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 1.0f, 1.0f }, m_SquareColor);
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);

	Hazel::Renderer2D::EndScene();

}



void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

	ImGui::ShowDemoWindow();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}