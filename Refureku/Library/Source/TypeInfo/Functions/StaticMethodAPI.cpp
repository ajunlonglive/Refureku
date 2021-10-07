#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"

#include "Refureku/TypeInfo/Functions/StaticMethodImpl.h"

using namespace rfk;

StaticMethodAPI::StaticMethodAPI(char const* name, std::size_t id, Type const& returnType,
								 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBaseAPI(new StaticMethodImpl(name, id, returnType, internalMethod, flags, outerEntity))
{
}

StaticMethodAPI::StaticMethodAPI(StaticMethodAPI&&) noexcept = default;

StaticMethodAPI::~StaticMethodAPI() noexcept = default;