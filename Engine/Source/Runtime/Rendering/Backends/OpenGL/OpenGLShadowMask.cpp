#include "OpenGLShadowMask.h"
#include "Core/Log.h"

#include <glad/glad.h>

Firebox::OpenGL::OpenGLShadowMask::OpenGLShadowMask()
{
}

Firebox::OpenGL::OpenGLShadowMask::~OpenGLShadowMask()
{
}

void Firebox::OpenGL::OpenGLShadowMask::BindShadowMask()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowMaskInfo.ShadowMaskFBO);
}

void Firebox::OpenGL::OpenGLShadowMask::BindShadowMaskTexture()
{
    glActiveTexture(GL_TEXTURE30);
    glBindTexture(GL_TEXTURE_2D, m_ShadowMaskInfo.ShadowMaskTexture);
}

void Firebox::OpenGL::OpenGLShadowMask::UnbindShadowMask()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Firebox::OpenGL::OpenGLShadowMask::ResizeShadowMask(uint width, uint height)
{
    m_ShadowMaskInfo.Width = width;
    m_ShadowMaskInfo.Height = height;
    Invalidate();
}

void Firebox::OpenGL::OpenGLShadowMask::ClearShadowMask()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Firebox::OpenGL::OpenGLShadowMask::Invalidate()
{
    if (m_ShadowMaskInfo.ShadowMaskFBO)
    {
        glDeleteFramebuffers(1, &m_ShadowMaskInfo.ShadowMaskFBO);
        glDeleteTextures(1, &m_ShadowMaskInfo.ShadowMaskTexture);
    }

    glGenFramebuffers(1, &m_ShadowMaskInfo.ShadowMaskFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowMaskInfo.ShadowMaskFBO);

    glGenTextures(1, &m_ShadowMaskInfo.ShadowMaskTexture);
    glBindTexture(GL_TEXTURE_2D, m_ShadowMaskInfo.ShadowMaskTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_ShadowMaskInfo.Width, m_ShadowMaskInfo.Height, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ShadowMaskInfo.ShadowMaskTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        FB_CORE_ERROR("Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
