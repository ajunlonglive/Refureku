/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
template <typename... Args>
Pimpl<T>::Pimpl(Args&&... arguments):
	_implementation{ new T(std::forward<Args>(arguments)...) },
	_owning{true}
{
}

template <typename T>
Pimpl<T>::Pimpl(T* implementation) noexcept:
	_implementation{implementation},
	_owning{false}
{
}

template <typename T>
Pimpl<T>::Pimpl(Pimpl const& other):
	_implementation{(other._implementation != nullptr) ? new T(*other._implementation) : nullptr},
	_owning{true}
{
}

template <typename T>
Pimpl<T>::Pimpl(Pimpl&& other) noexcept:
	_implementation{other._implementation},
	_owning{other._owning}
{
	other._implementation = nullptr;
}

template <typename T>
Pimpl<T>::~Pimpl()
{
	checkedDelete();
}

template <typename T>
void Pimpl<T>::checkedDelete()
{
	if (_implementation != nullptr)
	{
		if (_owning)
		{
			delete _implementation;
		}

		_implementation = nullptr;
	}
}

template <typename T>
T* Pimpl<T>::get() noexcept
{
	return _implementation;
}

template <typename T>
T const* Pimpl<T>::get() const noexcept
{
	return _implementation;
}

template <typename T>
void Pimpl<T>::set(T* implementation) noexcept
{
	//Free any implementation first
	checkedDelete();

	_implementation = implementation;
	_owning = false;
}

template <typename T>
Pimpl<T>& Pimpl<T>::operator=(Pimpl const& other)
{
	checkedDelete();

	_implementation = (other._implementation != nullptr) ? new T(*other._implementation) : nullptr;
	_owning = true;

	return *this;
}

template <typename T>
Pimpl<T>& Pimpl<T>::operator=(Pimpl&& other) noexcept
{
	checkedDelete();

	_implementation = other._implementation;
	_owning = other._owning;
	other._implementation = nullptr;

	return *this;
}

template <typename T>
T* Pimpl<T>::operator->() noexcept
{
	return _implementation;
}

template <typename T>
T const* Pimpl<T>::operator->() const noexcept
{
	return _implementation;
}

template <typename T>
T& Pimpl<T>::operator*() noexcept
{
	return *_implementation;
}

template <typename T>
T const& Pimpl<T>::operator*() const noexcept
{
	return *_implementation;
}