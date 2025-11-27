#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <limits>
#include <stdexcept>

template<typename T>
class Allocator 
{
public:
	Allocator() noexcept { }

	template<typename U>
	Allocator() noexcept { }

	T* allocate(size_t n)
	{
		if (n > std::numeric_limits<size_t>::max() / sizeof(T))
			throw std::bad_alloc();

		return static_cast<T*>(::operator new(n * sizeof(n)));
	}

	void deallocate(T* p, size_t)
	{
		::operator delete(p);
	}

	template<class U, class ... Args>
	void construct(U* p, Args&&... args)
	{
		::new ((void*)p) U(std::forward<Args>(args)...);
	}

	template<class U>
	void destroy(U* p)
	{
		p->~U();
	}
};

// since Allocator is stateless, any
// two random Allocators are interchangeable

template<typename T, typename U>
bool operator==(const Allocator<T>&, const Allocator<U>&)
{
	return true;
}

template<typename T, typename U>
bool operator!=(const Allocator<T>&, const Allocator<U>&)
{
	return false;
}

#endif // ALLOCATOR_HPP