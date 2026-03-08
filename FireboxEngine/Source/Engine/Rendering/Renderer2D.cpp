#include "Renderer2D.h"

Firebox::Renderer2D::Renderer2D() : m_RendererAPI(nullptr)
{
	m_RendererAPI = new RendererAPI();
	m_RendererAPI->Init();
}

Firebox::Renderer2D::~Renderer2D()
{
	delete m_RendererAPI;
}

void Firebox::Renderer2D::Render()
{
	m_RendererAPI->BindBuffers();
	m_RendererAPI->SetScreenColor(Vector4(0.39f, 0.58f, 0.93, 1.0f));
	m_RendererAPI->Clear();

	m_RendererAPI->RenderQuad();

	m_RendererAPI->UnbindBuffers();
}
