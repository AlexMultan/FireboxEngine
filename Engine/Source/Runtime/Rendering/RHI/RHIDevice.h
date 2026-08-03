#pragma once

#include "Core/Core.h"

namespace Firebox {

	class FIREBOX_API RHIDevice
	{
	public:
		~RHIDevice() {};

	protected:
		virtual void GetPhysicalDevice() = 0;
		virtual void CreateLogicalDevice() = 0;
	};
}