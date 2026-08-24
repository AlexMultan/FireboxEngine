#pragma once

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Buffers/Vertex.h"
#include "Rendering/Materials/Material.h"

namespace Firebox {

	class FIREBOX_API Skybox
	{
	public:
		Skybox();
		Skybox(const std::vector<String>& faces);
        inline const Ref<VertexArray>& GetVertexArray() const { return m_VAO; }
        inline const Ref<Shader>& GetShader() const { return m_SkyboxShader; }
        inline const Ref<Material>& GetMaterial() const { return m_SkyboxMaterial; }
        inline const std::vector<String>& GetFaces() const { return m_Faces; }

	private:
        Ref<VertexArray> m_VAO;
        Ref<VertexBuffer> m_VBO;
        Ref<IndexBuffer> m_IBO;
        Ref<Shader> m_SkyboxShader;
        Ref<Material> m_SkyboxMaterial;
        std::vector<String> m_Faces;

        float vertices[72] = {
            // Back face (-Z)
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,

            // Left face (-X)
            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,

            // Right face (+X)
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,

            // Front face (+Z)
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,

            // Top face (+Y)
            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,

            // Bottom face (-Y)
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
        };

        uint indices[36] = {
            0,  1,  2,   2,  3,  0,
            4,  5,  6,   6,  7,  4,
            8,  9, 10,  10, 11,  8,
            12, 13, 14,  14, 15, 12,
            16, 17, 18,  18, 19, 16,
            20, 21, 22,  22, 23, 20
        };
	};
}