#pragma once

#include "Core.h"

namespace Firebox {

	class FIREBOX_API UUID
	{
	public:
		UUID();
		UUID(uint64 uuid) : m_UUID(uuid){}

		operator uint64() const { return m_UUID; }
		bool operator==(const UUID& other) const { return m_UUID == other.m_UUID; }
		bool operator!=(const UUID& other) const { return m_UUID != other.m_UUID; }

	private:
		uint64 m_UUID;
	};
}

namespace std {

	template<>
	struct hash<Firebox::UUID>
	{
		size_t operator()(const Firebox::UUID& uuid) const
		{
			return hash<uint64>()((uint64)uuid);
		}
	};
}