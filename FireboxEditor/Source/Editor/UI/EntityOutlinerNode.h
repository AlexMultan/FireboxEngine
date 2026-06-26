#pragma once

#include "Engine/Utils/Types.h"

namespace FireboxEditor {

	class EntityOutlinerNode
	{
	public:
		bool DrawNode(const char* name, const uint64 id, bool isSelected);
	};
}