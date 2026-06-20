#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"

#include <vector>

namespace Firebox {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}
		FB_CORE_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		String Name;
		uint Size;
		uint Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const String& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat3:     return 3;
			case ShaderDataType::Mat4:     return 3;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
			}
			FB_CORE_ERROR("Unknown ShaderDataType!");
			return 0;
		}
		
	};
	class FIREBOX_API BufferLayout
	{
	public:
		BufferLayout() : m_Stride(0) {}
		BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	private:
		void CalculateOffsetsAndStride()
		{
			uint offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint m_Stride = 0;
	};
}