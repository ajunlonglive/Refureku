/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethodAPI::internalInvoke(ArgTypes&&... args) const noexcept
{
	return reinterpret_cast<NonMemberFunction<ReturnType(ArgTypes...)>*>(getInternalFunction())->operator()(std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethodAPI::invoke(ArgTypes&&... args) const
{
	return internalInvoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
}

template <typename ReturnType, typename... ArgTypes>
ReturnType StaticMethodAPI::checkedInvoke(ArgTypes&&... args) const
{
	checkReturnType<ReturnType>();
	checkParameterTypes<ArgTypes...>();

	return invoke<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
}