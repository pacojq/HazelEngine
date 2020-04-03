#pragma once

#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;

private:

	Hazel::OrthographicCameraController m_CameraController;

	// TEMP
	Hazel::Ref<Hazel::VertexArray> m_SquareVertexArray;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

	float m_TilingFactor;
	float m_Rotation;
	glm::vec4 m_FirstColor;
	glm::vec4 m_SecondColor;
	Hazel::Ref<Hazel::Texture2D> m_Texture;

};