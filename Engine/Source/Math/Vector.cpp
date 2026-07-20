#include "Vector.h"

Vec3::Vec3() : m_Data(0, 0, 0)
{

}

Vec3::Vec3(float x, float y, float z) : m_Data(x, y, z)
{

}

Vec3::Vec3(int x, int y, int z) : m_Data(x, y, z)
{

}

Vec3::Vec3(const glm::vec3& vector) : m_Data(vector)
{

}

glm::vec3& Vec3::get()
{
	return m_Data;
}

const glm::vec3 Vec3::get() const
{
	return m_Data;
}

float& Vec3::x()
{
	return m_Data.x;
}

float& Vec3::y()
{
	return m_Data.y;
}

float& Vec3::z()
{
	return m_Data.z;
}

const float Vec3::x() const
{
	return m_Data.x;
}

const float Vec3::y() const
{
	return m_Data.y;
}

const float Vec3::z() const
{
	return m_Data.z;
}

const Vec3 Vec3::ZeroVec()
{
	return Vec3(0, 0, 0);
}
