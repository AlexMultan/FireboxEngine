#include "RendererAPI.h"
#include "Engine/Rendering/API/OpenGL/OpenGLShader.h"
#include "Engine/Utils/OpenGLDebugger.h"

// This class is complete garbage and looks worse than shit. TO-DO: fix this bullshit.

Firebox::RendererAPI::RendererAPI()
{

}

Firebox::RendererAPI::~RendererAPI()
{

}

void Firebox::RendererAPI::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glCheckError();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexData), m_VertexData, GL_STATIC_DRAW);
	glCheckError();

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	glCheckError();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenTextures(1, &m_ViewportTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_ViewportTextureBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ViewportTextureBuffer, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FIREBOX_CORE_ERROR("Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_GLShader = OpenGLShader("../FireboxEngine/Source/Engine/Rendering/Shaders/GLSL/Base.vert", "../FireboxEngine/Source/Engine/Rendering/Shaders/GLSL/Base.frag");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(0);
}

void Firebox::RendererAPI::BindBuffers()
{
	glBindVertexArray(m_VAO);
	if (m_UseFramebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}
	
}

void Firebox::RendererAPI::UnbindBuffers()
{
	glBindVertexArray(0);
	if (m_UseFramebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void Firebox::RendererAPI::SetScreenColor(const Vector4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Firebox::RendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Firebox::RendererAPI::RenderQuad()
{
	//glBindVertexArray(m_VAO);
	m_GLShader.UseShader();
	m_GLShader.SetFloat4("u_Color", 0.3f, 0.1f, 0.6f, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Firebox::RendererAPI::ResizeFramebuffer(uint32_t width, uint32_t height)
{
	glBindTexture(GL_TEXTURE_2D, m_ViewportTextureBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}
