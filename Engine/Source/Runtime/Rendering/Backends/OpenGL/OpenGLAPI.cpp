#include "OpenGLAPI.h"
#include "OpenGLDebugger.h"
#include "Utils/DebugTools.h"
#include "Utils/Assert.h"

Firebox::OpenGL::OpenGLAPI::OpenGLAPI()
{
	FB_CORE_INFO("OpenGL version: {0}", (const char*)glGetString(GL_VERSION));

	const GLubyte* renderer = glGetString(GL_RENDERER);
	if (renderer) {
		FB_CORE_INFO("Device: {0}", (const char*)renderer);
	}
}

Firebox::OpenGL::OpenGLAPI::~OpenGLAPI()
{
	
}

void Firebox::OpenGL::OpenGLAPI::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glClearDepth(0.0f);
	glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Firebox::OpenGL::OpenGLAPI::ClearColor(const Vector4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Firebox::OpenGL::OpenGLAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
	FB_COUNT_DRAW_CALL;
}

void Firebox::OpenGL::OpenGLAPI::SetDepthFunc(APIEnum func)
{
	glDepthFunc(ToGLEnum(func));
}

void Firebox::OpenGL::OpenGLAPI::ClearDepth(float value)
{
	glClearDepth(value);
}

void Firebox::OpenGL::OpenGLAPI::Clear(APIEnum func)
{
	glClear(ToGLEnum(func));
}

void Firebox::OpenGL::OpenGLAPI::BindTexture(uint slot, uint textureID)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Firebox::OpenGL::OpenGLAPI::BindTextureArray(uint slot, uint textureID)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void Firebox::OpenGL::OpenGLAPI::BindFramebuffer(APIEnum target, uint framebuffer)
{
	glBindFramebuffer(ToGLEnum(target), framebuffer);
}

void Firebox::OpenGL::OpenGLAPI::UnbindFramebuffer(APIEnum target)
{
	glBindFramebuffer(ToGLEnum(target), 0);
}

void Firebox::OpenGL::OpenGLAPI::BufferSubData(APIEnum target, uint offset, size_t size, const void* data)
{
	glBufferSubData(ToGLEnum(target), offset, size, data);
}

void Firebox::OpenGL::OpenGLAPI::CullFace(APIEnum target)
{
	glCullFace(ToGLEnum(target));
}

GLenum Firebox::OpenGL::OpenGLAPI::ToGLEnum(APIEnum value)
{
	switch (value)
	{
		// Masks
		case APIEnum::API_DEPTH_BUFFER_BIT:   return GL_DEPTH_BUFFER_BIT;
		case APIEnum::API_STENCIL_BUFFER_BIT: return GL_STENCIL_BUFFER_BIT;
		case APIEnum::API_COLOR_BUFFER_BIT:   return GL_COLOR_BUFFER_BIT;

		// Booleans
		case APIEnum::API_FALSE: return GL_FALSE;
		case APIEnum::API_TRUE:  return GL_TRUE;

		// Primitive types
		case APIEnum::API_POINTS:         return GL_POINTS;
		case APIEnum::API_LINES:          return GL_LINES;
		case APIEnum::API_LINE_LOOP:      return GL_LINE_LOOP;
		case APIEnum::API_LINE_STRIP:     return GL_LINE_STRIP;
		case APIEnum::API_TRIANGLES:      return GL_TRIANGLES;
		case APIEnum::API_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
		case APIEnum::API_TRIANGLE_FAN:   return GL_TRIANGLE_FAN;
		case APIEnum::API_QUADS:          return GL_QUADS;

		// Depth/stencil comparison functions
		case APIEnum::API_NEVER:    return GL_NEVER;
		case APIEnum::API_LESS:     return GL_LESS;
		case APIEnum::API_EQUAL:    return GL_EQUAL;
		case APIEnum::API_LEQUAL:   return GL_LEQUAL;
		case APIEnum::API_GREATER:  return GL_GREATER;
		case APIEnum::API_NOTEQUAL: return GL_NOTEQUAL;
		case APIEnum::API_GEQUAL:   return GL_GEQUAL;
		case APIEnum::API_ALWAYS:   return GL_ALWAYS;

		// Blend factors
		case APIEnum::API_ZERO:                return GL_ZERO;
		case APIEnum::API_ONE:                 return GL_ONE;
		case APIEnum::API_SRC_COLOR:           return GL_SRC_COLOR;
		case APIEnum::API_ONE_MINUS_SRC_COLOR:  return GL_ONE_MINUS_SRC_COLOR;
		case APIEnum::API_SRC_ALPHA:            return GL_SRC_ALPHA;
		case APIEnum::API_ONE_MINUS_SRC_ALPHA:  return GL_ONE_MINUS_SRC_ALPHA;
		case APIEnum::API_DST_ALPHA:            return GL_DST_ALPHA;
		case APIEnum::API_ONE_MINUS_DST_ALPHA:  return GL_ONE_MINUS_DST_ALPHA;
		case APIEnum::API_DST_COLOR:            return GL_DST_COLOR;
		case APIEnum::API_ONE_MINUS_DST_COLOR:  return GL_ONE_MINUS_DST_COLOR;
		case APIEnum::API_SRC_ALPHA_SATURATE:   return GL_SRC_ALPHA_SATURATE;
		case APIEnum::API_FRAMEBUFFER:   return GL_FRAMEBUFFER;
		case APIEnum::API_UNIFORM_BUFFER:   return GL_UNIFORM_BUFFER;
		case APIEnum::API_BACK:   return GL_BACK;
		case APIEnum::API_FRONT:   return GL_FRONT;
	}

	FB_ASSERT(false, "Unsupported APIEnum value in OpenGLAPI::ToGLEnum");
	return 0;
}
