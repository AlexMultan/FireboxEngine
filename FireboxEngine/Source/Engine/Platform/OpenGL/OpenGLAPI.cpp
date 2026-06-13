#include "OpenGLAPI.h"
#include "Engine/Utils/OpenGLDebugger.h"

Firebox::OpenGL::OpenGLAPI::OpenGLAPI()
{
}

Firebox::OpenGL::OpenGLAPI::~OpenGLAPI()
{
	
}

void Firebox::OpenGL::OpenGLAPI::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Firebox::OpenGL::OpenGLAPI::SetScreenColor(const Vector4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Firebox::OpenGL::OpenGLAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Firebox::OpenGL::OpenGLAPI::SetViewport(uint x, uint y, uint width, uint height)
{
	glViewport(x, y, width, height);
}

void Firebox::OpenGL::OpenGLAPI::DrawIndexed(const Ref<VertexArray>& vao, uint indexCount)
{
	vao->Bind();
	uint count = indexCount ? indexCount : vao->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}