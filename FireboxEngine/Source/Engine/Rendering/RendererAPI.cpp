#include "RendererAPI.h"
#include "Engine/Utils/OpenGLDebugger.h"
#include "Engine/Math/MathUtils.h"
#include "Engine/Utils/DebugTools.h"
#include "Engine/Input/Input.h"
#include "Engine/Platform/OpenGL/Shaders/BaseShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// This class is complete garbage and looks worse than shit. TO-DO: fix this bullshit.

Firebox::RendererAPI::RendererAPI()
{
	
}

Firebox::RendererAPI::~RendererAPI()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteTextures(1, &m_ViewportTextureBuffer);
	glDeleteTextures(1, &m_TestTexture);
}


void Firebox::RendererAPI::Init()
{
	glEnable(GL_DEPTH_TEST);

	float m_VertexData[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		-0.9f,  0.2f, -0.9f,  0.0f, 1.0f,
		 0.9f,  0.2f, -0.9f,  1.0f, 1.0f,
		 0.9f,  0.2f,  0.9f,  1.0f, 0.0f,
		 0.9f,  0.2f,  0.9f,  1.0f, 0.0f,
		-0.9f,  0.2f,  0.9f,  0.0f, 0.0f,
		-0.9f,  0.2f, -0.9f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glCheckError();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexData), m_VertexData, GL_STATIC_DRAW);
	glCheckError();

	/*glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	glCheckError();*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

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

	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//m_GLShader = OpenGLShader("../FireboxEngine/Source/Engine/Rendering/Shaders/GLSL/Base.vert", "../FireboxEngine/Source/Engine/Rendering/Shaders/GLSL/Base.frag");
	m_BaseShader = Firebox::Shader::CreateFromSource(Firebox::Shaders::OpenGL::BaseVertex, Firebox::Shaders::OpenGL::BaseFragment);

	// Texture shit code that will need to be moved to its own class but I don't give a damn about that at the moment cause now I just trynna make this shit work more or less propertly

	glGenTextures(1, &m_TestTexture);
	glBindTexture(GL_TEXTURE_2D, m_TestTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("../FireboxEngine/TestResources/T_Sidewalk.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		FIREBOX_CORE_ERROR("Failed to load texture!");
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	if (m_ViewportSize.x <= 0.0f || m_ViewportSize.y <= 0.0f) return;
	m_LastMouseX = m_ViewportSize.x / 2.0f;
	m_LastMouseY = m_ViewportSize.y / 2.0f;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(0);
}

void Firebox::RendererAPI::BindBuffers()
{
	glBindVertexArray(m_VAO);
	if (m_IsEditorRendering)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}
}

void Firebox::RendererAPI::UnbindBuffers()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	if (m_IsEditorRendering)
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Firebox::RendererAPI::RenderQuad()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TestTexture);

	float firstMouseX;
	float firstMouseY;

	if (m_IsViewportFocused && Firebox::Input::IsMouseButtonClicked(Firebox::FBK_MOUSE_BUTTON_RIGHT))
	{
		firstMouseX = Firebox::Input::GetMousePosition().x;
		firstMouseY = Firebox::Input::GetMousePosition().y;

	}

	if (m_IsViewportFocused && Firebox::Input::IsMouseButtonDown(Firebox::FBK_MOUSE_BUTTON_RIGHT))
	{
		SDL_HideCursor();

		if (m_FirstMouseMovement)
		{
			m_LastMouseX = Firebox::Input::GetMousePosition().x;
			m_LastMouseY = Firebox::Input::GetMousePosition().y;
			m_FirstMouseMovement = false;
		}

		float xOffset = Firebox::Input::GetMousePosition().x - m_LastMouseX;
		float yOffset = m_LastMouseY - Firebox::Input::GetMousePosition().y;
		m_LastMouseX = Firebox::Input::GetMousePosition().x;
		m_LastMouseY = Firebox::Input::GetMousePosition().y;

		const float sensitivity = 0.1f;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		m_CameraYaw += xOffset;
		m_CameraPitch += yOffset;

		if (m_CameraPitch > 89.0f)
		{
			m_CameraPitch = 89.0f;
		}
		if (m_CameraPitch < -89.0f)
		{
			m_CameraPitch = -89.0f;
		}

		Vector3 direction;
		direction.x = cos(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));
		direction.y = sin(glm::radians(m_CameraPitch));
		direction.z = sin(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));
		m_CameraFront = glm::normalize(direction);

		if (Firebox::Input::IsKeyDown(Firebox::FBK_KEY_W))
		{
			m_CameraPosition += m_CameraSpeed * m_CameraFront;
		}
		if (Firebox::Input::IsKeyDown(Firebox::FBK_KEY_S))
		{
			m_CameraPosition -= m_CameraSpeed * m_CameraFront;
		}
		if (Firebox::Input::IsKeyDown(Firebox::FBK_KEY_A))
		{
			m_CameraPosition -= m_CameraSpeed * GetCameraRightVector();
		}
		if (Firebox::Input::IsKeyDown(Firebox::FBK_KEY_D))
		{
			m_CameraPosition += m_CameraSpeed * GetCameraRightVector();
		}
	}
	else if (Firebox::Input::IsMouseButtonReleased(Firebox::FBK_MOUSE_BUTTON_RIGHT))
	{
		SDL_ShowCursor();
	}
	
	view = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
	
	Mat4 projection;
	if (m_ViewportSize.x <= 0.0f || m_ViewportSize.y <= 0.0f) return;
	projection = glm::perspective(glm::radians(60.0f), m_ViewportSize.x / m_ViewportSize.y, 0.1f, 100.0f);
	
	Mat4 viewProjection = projection * view;

	m_BaseShader->UseShader();
	m_BaseShader->SetMat4("u_ViewProjection", viewProjection);
	for (uint i = 0; i < 11; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		m_BaseShader->SetMat4("u_Model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Firebox::RendererAPI::ResizeFramebuffer(uint32_t width, uint32_t height)
{
	m_ViewportSize = Vector2((float)width, (float)height);
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_ViewportTextureBuffer)
		glDeleteTextures(1, &m_ViewportTextureBuffer);

	glGenTextures(1, &m_ViewportTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_ViewportTextureBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ViewportTextureBuffer, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		FIREBOX_CORE_ERROR("Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Firebox::RendererAPI::ClearEditorViewportRenderingCache() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
