#pragma once

#include "Utils/Types.h"

#define MAX_BONE_INFLUENCE 4

namespace Firebox {

	struct Vertex
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 TexCoords;
		Vector3 Tangent;
		Vector3 Bitangent;
	};
}