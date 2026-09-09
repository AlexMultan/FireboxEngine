#pragma once

#include "Core/Core.h"

#include <atomic>
#include <utility>

class FIREBOX_API RefCounted
{
public:
	RefCounted() = default;
	virtual ~RefCounted() = default;

	RefCounted(const RefCounted&) {}
	RefCounted& operator=(const RefCounted&) { return *this; }

#pragma region Atomic Reference Counting
#if 0
	void AddRef() const
	{
		m_RefCount.fetch_add(1, std::memory_order_relaxed);
	}

	bool Release() const
	{
		if (m_RefCount.fetch_sub(1, std::memory_order_acq_rel) == 1)
		{
			return true;
		}
		return false;
	}

	int32_t RefCount() const { return m_RefCount.load(std::memory_order_relaxed); }
private:
	mutable std::atomic<int32_t> m_RefCount = 0;
#endif
#pragma endregion

	void AddRef() const
	{
		m_RefCount++;
	}

	bool Release() const
	{
		return --m_RefCount == 0;
	}

	int32_t RefCount() const { return m_RefCount; }
private:
	mutable int32_t m_RefCount = 0;
};

template<typename T>
class Ref
{
public:
	Ref() = default;
	Ref(std::nullptr_t) {}

	explicit Ref(T* ptr) : m_Ptr(ptr)
	{
		if (m_Ptr)
			m_Ptr->AddRef();
	}

	Ref(const Ref& other) : m_Ptr(other.m_Ptr)
	{
		if (m_Ptr)
			m_Ptr->AddRef();
	}

	Ref(Ref&& other) noexcept : m_Ptr(other.m_Ptr)
	{
		other.m_Ptr = nullptr;
	}

	template<typename U>
	Ref(const Ref<U>& other) : m_Ptr(other.Get())
	{
		if (m_Ptr)
			m_Ptr->AddRef();
	}

	~Ref() { Reset(); }

	Ref& operator=(const Ref& other)
	{
		if (this != &other)
		{
			if (other.m_Ptr)
				other.m_Ptr->AddRef();
			Reset();
			m_Ptr = other.m_Ptr;
		}
		return *this;
	}

	Ref& operator=(Ref&& other) noexcept
	{
		if (this != &other)
		{
			Reset();
			m_Ptr = other.m_Ptr;
			other.m_Ptr = nullptr;
		}
		return *this;
	}

	Ref& operator=(std::nullptr_t)
	{
		Reset();
		return *this;
	}

	void Reset()
	{
		if (m_Ptr && m_Ptr->Release())
		{
			delete m_Ptr;
		}
		m_Ptr = nullptr;
	}

	T* Get() const { return m_Ptr; }
	T* operator->() const { return m_Ptr; }
	T& operator*() const { return *m_Ptr; }
	explicit operator bool() const { return m_Ptr != nullptr; }

	bool operator==(const Ref& other) const { return m_Ptr == other.m_Ptr; }
	bool operator!=(const Ref& other) const { return m_Ptr != other.m_Ptr; }

private:
	T* m_Ptr = nullptr;
};

template<typename T, typename... Args>
Ref<T> CreateRef(Args&&... args)
{
	return Ref<T>(new T(std::forward<Args>(args)...));
}