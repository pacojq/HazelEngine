#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>



/*
#include <chrono>


class Timer
{
public:
	Timer(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;
		
		float duration = (end - start) * 0.001f; // Microseconds to milliseconds

		std::cout << m_Name << ": " << duration << "ms" << std::endl;
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};
*/












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

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.5f }, { 0.8f, 0.8f }, m_Rotation, m_SecondColor);
	Hazel::Renderer2D::DrawQuad({ 0.25f, -0.25f }, { 1.2f, 1.2f }, m_FirstColor);
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, m_TilingFactor, m_SecondColor);

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

	//ImGui::ShowDemoWindow();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}