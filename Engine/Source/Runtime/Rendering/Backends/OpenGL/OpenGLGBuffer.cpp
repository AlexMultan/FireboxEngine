#include "OpenGLGBuffer.h"
#include "Core/Log.h"
#include "OpenGLDebugger.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLGBuffer::OpenGLGBuffer()
{
    
}

Firebox::OpenGL::OpenGLGBuffer::~OpenGLGBuffer()
{
}

void Firebox::OpenGL::OpenGLGBuffer::BindGBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferInfo.Buffer);
}

void Firebox::OpenGL::OpenGLGBuffer::BindGBufferPositionNormal()
{
    glActiveTexture(GL_TEXTURE27);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.Position);

    glActiveTexture(GL_TEXTURE28);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.NormalMetallic);
}

void Firebox::OpenGL::OpenGLGBuffer::BindGBufferAO()
{
    glActiveTexture(GL_TEXTURE23);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.AmbientOcclusion);
}

void Firebox::OpenGL::OpenGLGBuffer::BindGBufferAlbedo()
{
    glActiveTexture(GL_TEXTURE29);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.AlbedoRough);
}

void Firebox::OpenGL::OpenGLGBuffer::UnbindGBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLGBuffer::BlitGBuffer()
{
    glBlitFramebuffer(0, 0, m_GBufferInfo.Width, m_GBufferInfo.Height, 0, 0, m_GBufferInfo.Width, m_GBufferInfo.Height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void Firebox::OpenGL::OpenGLGBuffer::ReadGBuffer()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_GBufferInfo.Buffer);
}

void Firebox::OpenGL::OpenGLGBuffer::DrawGBuffer(uint targetFBO)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, targetFBO);
}

void Firebox::OpenGL::OpenGLGBuffer::ResizeGBuffer(uint width, uint height)
{
    m_GBufferInfo.Width = width;
    m_GBufferInfo.Height = height;
    Invalidate();
}

void Firebox::OpenGL::OpenGLGBuffer::ClearGBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

uint Firebox::OpenGL::OpenGLGBuffer::GetColorAttachment() const
{
    return m_GBufferInfo.Buffer;
}

Firebox::GBufferInfo& Firebox::OpenGL::OpenGLGBuffer::GetGBufferInfo()
{
    return m_GBufferInfo;
}

void Firebox::OpenGL::OpenGLGBuffer::Invalidate()
{
    if (m_GBufferInfo.Buffer)
    {
        glDeleteFramebuffers(1, &m_GBufferInfo.Buffer);
        glDeleteTextures(1, &m_GBufferInfo.Position);
        glDeleteTextures(1, &m_GBufferInfo.NormalMetallic);
        glDeleteTextures(1, &m_GBufferInfo.AlbedoRough);
        glDeleteTextures(1, &m_GBufferInfo.AmbientOcclusion);
        glDeleteRenderbuffers(1, &m_GBufferInfo.RenderBuffer);
    }

    glGenFramebuffers(1, &m_GBufferInfo.Buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferInfo.Buffer);

    glGenTextures(1, &m_GBufferInfo.Position);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.Position);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_GBufferInfo.Width, m_GBufferInfo.Height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GBufferInfo.Position, 0);

    glGenTextures(1, &m_GBufferInfo.NormalMetallic);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.NormalMetallic);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_GBufferInfo.Width, m_GBufferInfo.Height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_GBufferInfo.NormalMetallic, 0);

    glGenTextures(1, &m_GBufferInfo.AlbedoRough);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.AlbedoRough);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_GBufferInfo.Width, m_GBufferInfo.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_GBufferInfo.AlbedoRough, 0);

    glGenTextures(1, &m_GBufferInfo.AmbientOcclusion);
    glBindTexture(GL_TEXTURE_2D, m_GBufferInfo.AmbientOcclusion);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_GBufferInfo.Width, m_GBufferInfo.Height, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_GBufferInfo.AmbientOcclusion, 0);

    m_GBufferInfo.GBufferAttachments[0] = GL_COLOR_ATTACHMENT0;
    m_GBufferInfo.GBufferAttachments[1] = GL_COLOR_ATTACHMENT1;
    m_GBufferInfo.GBufferAttachments[2] = GL_COLOR_ATTACHMENT2;
    m_GBufferInfo.GBufferAttachments[3] = GL_COLOR_ATTACHMENT3;
    glDrawBuffers(4, m_GBufferInfo.GBufferAttachments);

    glGenRenderbuffers(1, &m_GBufferInfo.RenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_GBufferInfo.RenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_GBufferInfo.Width, m_GBufferInfo.Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_GBufferInfo.RenderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        FB_CORE_ERROR("GBuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
