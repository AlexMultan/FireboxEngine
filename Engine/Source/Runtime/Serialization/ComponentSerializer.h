#pragma once

#include "Components/Components.h"
#include "JsonAlias.h"

namespace nlohmann {

	template<>
	struct adl_serializer<Vector2>
	{
		static void to_json(JSON& j, const Vector2& v)
		{
			j = JSON{ {"X", v.x}, {"Y", v.y} };
		}

		static void from_json(const JSON& j, Vector2& v)
		{
			j.at("X").get_to(v.x);
			j.at("Y").get_to(v.y);
		}
	};

	template<>
	struct adl_serializer<Vector3>
	{
		static void to_json(JSON& j, const Vector3& v)
		{
			j = JSON{ {"X", v.x}, {"Y", v.y}, {"Z", v.z} };
		}

		static void from_json(const JSON& j, Vector3& v)
		{
			j.at("X").get_to(v.x);
			j.at("Y").get_to(v.y);
			j.at("Z").get_to(v.z);
		}
	};

	template<>
	struct adl_serializer<Vector4>
	{
		static void to_json(JSON& j, const Vector4& v)
		{
			j = JSON{ {"R", v.r}, {"G", v.g}, {"B", v.b}, {"A", v.a} };
		}

		static void from_json(const JSON& j, Vector4& v)
		{
			j.at("R").get_to(v.r);
			j.at("G").get_to(v.g);
			j.at("B").get_to(v.b);
			j.at("A").get_to(v.a);
		}
	};

	template<>
	struct adl_serializer<TransformComponent>
	{
		static void to_json(JSON& j, const TransformComponent& transform)
		{
			j = JSON{
				{"Position", transform.Position},
				{"Rotation", transform.Rotation},
				{"Scale", transform.Scale}
			};
		}

		static void from_json(const JSON& j, TransformComponent& transform)
		{
			j.at("Position").get_to(transform.Position);
			j.at("Rotation").get_to(transform.Rotation);
			j.at("Scale").get_to(transform.Scale);
		}
	};

	template<>
	struct adl_serializer<TagComponent>
	{
		static void to_json(JSON& j, const TagComponent& tag)
		{
			j = JSON{ {"Tag", tag.Tag} };
		}

		static void from_json(const JSON& j, TagComponent& tag)
		{
			j.at("Tag").get_to(tag.Tag);
		}
	};

#if 0
	template<>
	struct adl_serializer<SkyboxComponent>
	{
		static void to_json(JSON& j, const SkyboxComponent& sb)
		{
			if (sb.Skybox)
				j = JSON{ {"Faces", sb.Skybox->GetFaces()} };
			else
				j = JSON{ {"Faces", std::vector<String>{}} };
		}

		static void from_json(const JSON& j, SkyboxComponent& sb)
		{
			std::vector<String> faces;
			j.at("Faces").get_to(faces);
			if (!faces.empty())
				sb.Skybox = CreateRef<Firebox::Skybox>(faces);
		}
	};
#endif

	template<>
	struct adl_serializer<DirectionalLightComponent>
	{
		static void to_json(JSON& j, const DirectionalLightComponent& dlc)
		{
			j = JSON{
				{"Direction", dlc.Direction},
				{"Color", dlc.Color},
				{"Intensity", dlc.Intensity}
			};
		}

		static void from_json(const JSON& j, DirectionalLightComponent& dlc)
		{
			j.at("Direction").get_to(dlc.Direction);
			j.at("Color").get_to(dlc.Color);
			j.at("Intensity").get_to(dlc.Intensity);
			Firebox::Renderer3D::SetDirectionalLight(dlc);
		}
	};

	template<>
	struct adl_serializer<PointLightComponent>
	{
		static void to_json(JSON& j, const PointLightComponent& plc)
		{
			j = JSON{
				{"Position", plc.Position},
				{"Color", plc.Color},
				{"Constant", plc.Constant},
				{"Linear", plc.Linear},
				{"Quadratic", plc.Quadratic}
			};
		}

		static void from_json(const JSON& j, PointLightComponent& plc)
		{
			j.at("Position").get_to(plc.Position);
			j.at("Color").get_to(plc.Color);
			j.at("Constant").get_to(plc.Constant);
			j.at("Linear").get_to(plc.Linear);
			j.at("Quadratic").get_to(plc.Quadratic);
			Firebox::Renderer3D::GetPointLights().emplace_back(plc);
		}
	};

	template<>
	struct adl_serializer<SpotLightComponent>
	{
		static void to_json(JSON& j, const SpotLightComponent& slc)
		{
			j = JSON{
				{"Position", slc.Position},
				{"Direction", slc.Direction},
				{"Color", slc.Color},
				{"Constant", slc.Constant},
				{"Linear", slc.Linear},
				{"Quadratic", slc.Quadratic},
				{"CutOff", slc.CutOff},
				{"OuterCutOff", slc.OuterCutOff}
			};
		}

		static void from_json(const JSON& j, SpotLightComponent& slc)
		{
			j.at("Position").get_to(slc.Position);
			j.at("Direction").get_to(slc.Direction);
			j.at("Color").get_to(slc.Color);
			j.at("Constant").get_to(slc.Constant);
			j.at("Linear").get_to(slc.Linear);
			j.at("Quadratic").get_to(slc.Quadratic);
			j.at("CutOff").get_to(slc.CutOff);
			j.at("OuterCutOff").get_to(slc.OuterCutOff);
			Firebox::Renderer3D::GetSpotLights().emplace_back(slc);
		}
	};

	template<>
	struct adl_serializer<Ref<Firebox::Texture>>
	{
		static void to_json(JSON& j, const Ref<Firebox::Texture>& texture)
		{
			if (!texture) { j = nullptr; return; }
			j = JSON{ {"Path", texture->GetTexturePath()}};
		}

		static void from_json(const JSON& j, Ref<Firebox::Texture>& texture)
		{
			if (j.is_null()) { texture = nullptr; return; }
			String path = j.at("Path").get<String>();
			texture = Firebox::Texture::Create(path);
		}
	};

	template<>
	struct adl_serializer<Ref<Firebox::Material>>
	{
		static void to_json(JSON& j, const Ref<Firebox::Material>& mat)
		{
			if (!mat) { j = nullptr; return; }

			j = JSON{
				{"Diffuse", mat->GetDiffuse()},
				{"Roughness", mat->GetRoughness()},
				{"Metallic", mat->GetMetallic()},
				{"Normal", mat->GetNormal()},
				{"Diffuse Color", mat->GetDiffuseColor()},
				{"Roughness Value", mat->GetRoughnessValue()},
				{"Metallic Value", mat->GetMetallicValue()}
			};
		}

		static void from_json(const JSON& j, Ref<Firebox::Material>& mat)
		{
			if (j.is_null()) { mat = nullptr; return; }
			mat = CreateRef<Firebox::Material>();

			if (j.contains("Diffuse") && !j.at("Diffuse").is_null())
				mat->SetDiffuseTexture(j.at("Diffuse").get<Ref<Firebox::Texture>>());
			else
				mat->SetDiffuseColor(j.at("Diffuse Color").get<Vector4>());

			if (j.contains("Roughness") && !j.at("Roughness").is_null())
				mat->SetRoughnessTexture(j.at("Roughness").get<Ref<Firebox::Texture>>());
			else
				mat->SetRoughnessValue(j.at("Roughness Value").get<float>());

			if (j.contains("Metallic") && !j.at("Metallic").is_null())
				mat->SetMetallicTexture(j.at("Metallic").get<Ref<Firebox::Texture>>());
			else
				mat->SetMetallicValue(j.at("Metallic Value").get<float>());

			if (j.contains("Normal") && !j.at("Normal").is_null())
				mat->SetNormalTexture(j.at("Normal").get<Ref<Firebox::Texture>>());
		}
	};

	template<>
	struct adl_serializer<StaticMeshComponent>
	{
		static void to_json(JSON& j, const StaticMeshComponent& mesh)
		{
			if (!mesh.StaticMesh) { j = nullptr; return; }

			j = JSON{
				{"Model Path", mesh.StaticMesh->GetDirectory()},
				{"Materials", mesh.StaticMesh->GetMaterials()}
			};
		}

		static void from_json(const JSON& j, StaticMeshComponent& mesh)
		{
			if (j.is_null()) { mesh.StaticMesh = nullptr; return; }
			
			if (j.contains("Model Path") && !j.at("Model Path").is_null())
			{
				String path = j.at("Model Path").get<String>();
				mesh.StaticMesh = CreateRef<Firebox::StaticMesh>(path);

				if (j.contains("Materials") && !j.at("Materials").is_null())
				{
					const JSON& materials = j.at("Materials");
					for (size_t i = 0; i < mesh.StaticMesh->GetMaterials().size(); i++)
					{
						mesh.StaticMesh->SetMaterial(i, materials.at(i).get<Ref<Firebox::Material>>());
					}
				}
			}
		}
	};
}