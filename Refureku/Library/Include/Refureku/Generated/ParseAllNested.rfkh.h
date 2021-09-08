#pragma once

#include "EntityMacros.h"

#include <cstddef>

#include <Refureku/Misc/DisableWarningMacros.h>
#include <Refureku/Utility/CodeGenerationHelpers.h>
#include <Refureku/TypeInfo/Archetypes/GetArchetype.h>
#include <Refureku/TypeInfo/Archetypes/Class.h>
#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>
#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>
namespace rfk {class NamespaceFragment;class Function;class Variable;}
#include <Refureku/TypeInfo/Entity/EEntityKind.h>

#define ParseAllNested_GENERATED	\
friend rfk::Struct;\
friend rfk::CodeGenerationHelpers;\
friend implements_template1__rfk_registerChildClass<ParseAllNested, void, void(rfk::Struct&)>; \
private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept {\
rfk::CodeGenerationHelpers::registerChildClass<rfk::Property, ChildClass>(childClass);\
rfk::Struct const& thisClass = staticGetArchetype();\
if constexpr (!std::is_same_v<ChildClass, ParseAllNested>) const_cast<rfk::Struct&>(thisClass).subclasses.insert(&childClass);\
\
}public: static rfk::Struct const& staticGetArchetype() noexcept;\
public: virtual rfk::Struct const& getArchetype() const noexcept override;\
_RFK_UNPACK_IF_NOT_PARSING(private: static rfk::ArchetypeRegisterer _rfk_archetypeRegisterer;\
)\
public: static constexpr rfk::EEntityKind targetEntityKind = rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct;\
virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;\


#define File_ParseAllNested_GENERATED	\
namespace rfk { template <> rfk::Archetype const* getArchetype<ParseAllNested>() noexcept; }\


