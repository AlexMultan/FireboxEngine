#pragma once

#include <glm/glm.hpp>

class Vec3
{
private:
	glm::vec3 m_Data;

public:

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(int x, int y, int z);
	Vec3(const glm::vec3& vector);
	~Vec3() = default;

	glm::vec3& get();
	const glm::vec3 get() const;

	float& x();
	float& y();
	float& z();
	const float x() const;
	const float y() const;
	const float z() const;

	static const Vec3 ZeroVec();
};