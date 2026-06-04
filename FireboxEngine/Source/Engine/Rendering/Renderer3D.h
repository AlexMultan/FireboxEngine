#pragma once

#include "Engine/Rendering/RendererAPI.h"
#include "Engine/Rendering/Resources/Shader.h"
#include "Engine/Rendering/Resources/Material.h"
#include "Engine/Rendering/Resources/Mesh.h"
#include "Engine/Components/Components.h"
#include "Engine/Components/LightComponents.h"
#include "Engine/Rendering/Camera/Camera.h"

namespace Firebox {

	class FIREBOX_API Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const DirectionalLightComponent& directionalLight);
		static void EndScene();

		static void DrawMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const TransformComponent& transform);

		//static RendererAPI* GetAPI() { return s_RendererAPI.get(); }

		static Ref<Shader> GetBaseShader();
		static Ref<Shader> GetLightShader();

	private:
		static void Flush();

		struct RenderCommand
		{
			Ref<VertexArray> VAO;
			Ref<Material> Material;
			Mat4 Transform;
			Mat4 InverseNormal;
		};

		struct Renderer3DData
		{
			Scope<RendererAPI> RendererAPI;
			std::vector<RenderCommand> RenderQueue;
			Ref<Shader> BaseShader;
			Ref<Shader> LightShader;
			Mat4 ViewProjectionMatrix;
			Vector3 CameraPosition;
			DirectionalLightComponent DirectionalLight;
		};

		static Renderer3DData s_Data;
	};
}