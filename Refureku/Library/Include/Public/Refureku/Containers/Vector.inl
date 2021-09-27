/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector() noexcept:
	_data{nullptr},
	_size{0u},
	_capacity{0u}
{
	reserve(2u);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector const& other) noexcept(std::is_nothrow_destructible_v<T>):
	_data{nullptr},
	_size{0u},
	_capacity{0u}
{
	resize(other._size);

	copyElements(other.data(), data(), other._size);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other) noexcept:
	_data{other._data},
	_size{other._size},
	_capacity{other._capacity}
{
	other._data		= nullptr;
	other._size		= 0u;
	other._capacity	= 0u;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector() noexcept(std::is_nothrow_destructible_v<T>)
{
	checkedDelete();
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::constructElements(T* from, std::size_t count) noexcept(std::is_nothrow_default_constructible_v<T>)
{
	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, from + i);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::copyElements(T const* from, T* to, std::size_t count) noexcept(std::is_nothrow_copy_constructible_v<T>)
{
	static_assert(std::is_copy_constructible_v<T>, "Can't call copyElements on a non-copyable type T.");

	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, to + i, *(from + i));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::moveElements(T* from, T* to, std::size_t count) noexcept(std::is_nothrow_move_constructible_v<T>)
{
	static_assert(std::is_move_constructible_v<T>, "Can't call moveElements on a non-moveable type T.");

	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::construct(_allocator, to + i, std::move(*(from + i)));
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::destroyElements(T* from, std::size_t count) noexcept(std::is_nothrow_destructible_v<T>)
{
	for (std::size_t i = 0u; i < count; i++)
	{
		AllocTraits::destroy(_allocator, from + i);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::checkedDelete() noexcept(std::is_nothrow_destructible_v<T>)
{
	if (_data != nullptr)
	{
		destroyElements(data(), _size);
		
		_allocator.deallocate(_data, _capacity);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reallocateIfFull()
{
	if (_size == _capacity)
	{
		reserve(_capacity * 2);
	}
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::front() noexcept
{
	assert(!empty());

	return *data();
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::front() const noexcept
{
	assert(!empty());

	return *data();
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::back() noexcept
{
	assert(!empty());

	return *(data() + _size - 1);
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::back() const noexcept
{
	assert(!empty());

	return *(data() + _size - 1);
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::data() noexcept
{
	//TODO: if using small vector, return _staticStorage instead
	return _data;
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::data() const noexcept
{
	//TODO: if using small vector, return _staticStorage instead
	return _data;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(std::size_t capacity)
{
	if (capacity > _capacity)
	{
		T* newData = reinterpret_cast<T*>(_allocator.allocate(capacity));

		if (_data != nullptr)
		{
			//Move elements if possible
			if constexpr (std::is_move_constructible_v<T>)
			{
				moveElements(data(), newData, _size);
			}
			else //Copy elements otherwise
			{
				copyElements(data(), newData, _size);
				destroyElements(data(), _size);
			}

			//Release previously allocated memory
			_allocator.deallocate(_data, _capacity);
		}

		_data		= newData;
		_capacity	= capacity;
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(std::size_t size)
{
	if (size > _size)
	{
		reserve(size);

		//Construct new elements
		constructElements(end(), size - _size);
	}
	else if (size < _size)
	{
		//Destroy overflowing elements
		destroyElements(end(), _size - size);
	}

	_size = size;
}

template <typename T, typename Allocator>
std::size_t	Vector<T, Allocator>::size() const noexcept
{
	return _size;
}

template <typename T, typename Allocator>
std::size_t Vector<T, Allocator>::capacity() const noexcept
{
	return _capacity;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return _size == 0u;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::clear() noexcept(std::is_nothrow_destructible_v<T>)
{
	destroyElements(data(), _size);

	_size = 0u;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T const& value)
{
	reallocateIfFull();

	AllocTraits::construct(_allocator, end(), value);
	_size++;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T&& value)
{
	reallocateIfFull();

	AllocTraits::construct(_allocator, end(), std::forward<T>(value));
	_size++;
}

template <typename T, typename Allocator>
template <typename... Args>
T& Vector<T, Allocator>::emplace_back(Args&&... args)
{
	reallocateIfFull();

	AllocTraits::construct(_allocator, end(), std::forward<Args>(args)...);
	_size++;

	return back();
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::begin() noexcept
{
	return data();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::begin() const noexcept
{
	return cbegin();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::cbegin() const noexcept
{
	return data();
}

template <typename T, typename Allocator>
T* Vector<T, Allocator>::end() noexcept
{
	return data() + _size;
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::end() const noexcept
{
	return cend();
}

template <typename T, typename Allocator>
T const* Vector<T, Allocator>::cend() const noexcept
{
	return data() + _size;
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](std::size_t index) noexcept
{
	return *(data() + index);
}

template <typename T, typename Allocator>
T const& Vector<T, Allocator>::operator[](std::size_t index) const noexcept
{
	return *(data() + index);
}