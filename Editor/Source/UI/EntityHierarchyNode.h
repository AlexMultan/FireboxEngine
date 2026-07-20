#pragma once

#include "Utils/Types.h"

namespace EditorUI {

	class EntityHierarchyNode
	{
	public:
		static bool DrawNode(const char* name, const uint64 id, bool isSelected);
	};
}