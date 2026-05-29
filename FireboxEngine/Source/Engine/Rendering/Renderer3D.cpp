#include "Renderer3D.h"
#include "Engine/Core/Log.h"

Firebox::Renderer3D::Renderer3D() : m_RendererAPI(nullptr)
{
	m_RendererAPI = new RendererAPI();
	m_RendererAPI->Init();
}

Firebox::Renderer3D::~Renderer3D()
{
	delete m_RendererAPI;
}

void Firebox::Renderer3D::OnTick(float deltaTime)
{
	
}

void Firebox::Renderer3D::OnRender()
{
	m_RendererAPI->BindBuffers();
	m_RendererAPI->SetScreenColor(Vector4(0.086f, 0.086f, 0.086f, 1.0f));
	m_RendererAPI->Clear();

	m_RendererAPI->RenderQuad();

	m_RendererAPI->UnbindBuffers();
}

