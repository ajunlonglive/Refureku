/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>	//std::shared_ptr
#include <cassert>
#include <iostream>

#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Entity/EntityHash.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

namespace rfk
{
	class Database::DatabaseImpl final
	{
		public:
			using EntitiesById					= std::unordered_set<Entity const*, EntityPtrIdHash, EntityPtrIdEqual>;
			using NamespacesByName				= std::unordered_set<Namespace const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using StructsByName					= std::unordered_set<Struct const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using ClassesByName					= std::unordered_set<Class const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using EnumsByName					= std::unordered_set<Enum const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using VariablesByName				= std::unordered_set<Variable const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using FunctionsByName				= std::unordered_multiset<Function const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using FundamentalArchetypesByName	= std::unordered_set<FundamentalArchetype const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using GenNamespaces					= std::unordered_map<std::size_t, std::shared_ptr<Namespace>>;
			
		private:
			/** Collection of all registered entities hashed by Id.  */
			EntitiesById				_entitiesById;

			/** Collection of all file level namespaces hashed by name. */
			NamespacesByName			_fileLevelNamespacesByName;

			/** Collection of all file level structs hashed by name. */
			StructsByName				_fileLevelStructsByName;

			/** Collection of all file level classes hashed by name. */
			ClassesByName				_fileLevelClassesByName;

			/** Collection of all file level enums hashed by name. */
			EnumsByName					_fileLevelEnumsByName;

			/** Collection of all file level variables hashed by name. */
			VariablesByName				_fileLevelVariablesByName;

			/** Collection of all file level functions hashed by name. */
			FunctionsByName				_fileLevelFunctionsByName;

			/** Collection of all fundamental archetypes hashed by name. */
			FundamentalArchetypesByName	_fundamentalArchetypes;

			/** Collection of namespace objects generated by the database. */
			GenNamespaces				_generatedNamespaces;

			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param s The parent struct.
			*/
			inline void		registerSubEntities(Struct const& s)		noexcept;

			/**
			*	@brief Remove all nested entities from the _entitiesById map.
			*	
			*	@param s The parent struct.
			*/
			inline void		unregisterSubEntities(Struct const& s)	noexcept;

			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param e The parent enum.
			*/
			inline void		registerSubEntities(Enum const& e)		noexcept;

			/**
			*	@brief Remove all nested entities from the _entitiesById map.
			*	
			*	@param e The parent enum.
			*/
			inline void		unregisterSubEntities(Enum const& e)		noexcept;

		public:
			DatabaseImpl()	= default;
			~DatabaseImpl()	= default;
			
			/**
			*	@brief Register a file level entity to the database (add it to both _entitiesById & _fileLevelEntitiesByName).
			*	
			*	@param entity						The entity to register.
			*	@param shouldRegisterSubEntities	Should sub entities be registered by id recursively?
			*/
			inline void											registerFileLevelEntity(Entity const&	entity,
																						bool				shouldRegisterSubEntities)	noexcept;

			/**
			*	@brief Register an entity to the database.
			*	
			*	@param entity						The entity to register.
			*	@param shouldRegisterSubEntities	Should sub entities be registered recursively?
			*/
			inline void											registerEntityId(Entity const&	entity,
																				 bool				shouldRegisterSubEntities)			noexcept;

			/**
			*	@brief Unregister an entity from the database.
			*	
			*	@param entity						The entity to unregister.
			*	@param shouldUnregisterSubEntities	Should sub entities be unregistered recursively?
			*/
			inline void											unregisterEntity(Entity const&	entity,
																				 bool				shouldUnregisterSubEntities)		noexcept;

			/**
			*	@brief	Check that a namespace is still referenced by some namespace fragment.
			*			If not, remove it from the database.
			*
			*	@param npPtr Pointer to the namespace to check.
			*/
			inline void											checkNamespaceRefCount(std::shared_ptr<Namespace> const& npPtr)		noexcept;

			/**
			*	@brief Get the namespace with the given name and id. If it doesn't exist yet, create and register it right away.
			* 
			*	@param name Name of the searched namespace.
			*	@param id	Id of the namespace.
			* 
			*	@return A shared_ptr to the retrieved namespace.
			*/
			RFK_NODISCARD inline std::shared_ptr<Namespace>	getOrCreateNamespace(char const*	name,
																					 std::size_t	id,
																					 bool			isFileLevelNamespace)				noexcept;

			/**
			*	@brief Getters for each field.
			*/
			RFK_NODISCARD inline EntitiesById const&				getEntitiesById()					const	noexcept;
			RFK_NODISCARD inline NamespacesByName const&			getFileLevelNamespacesByName()		const	noexcept;
			RFK_NODISCARD inline StructsByName const&				getFileLevelStructsByName()			const	noexcept;
			RFK_NODISCARD inline ClassesByName const&				getFileLevelClassesByName()			const	noexcept;
			RFK_NODISCARD inline EnumsByName const&					getFileLevelEnumsByName()			const	noexcept;
			RFK_NODISCARD inline VariablesByName const&				getFileLevelVariablesByName()		const	noexcept;
			RFK_NODISCARD inline FunctionsByName const&				getFileLevelFunctionsByName()		const	noexcept;
			RFK_NODISCARD inline FundamentalArchetypesByName const&	getFundamentalArchetypesByName()	const	noexcept;
			RFK_NODISCARD inline GenNamespaces const&				getGeneratedNamespaces()			const	noexcept;
	};

	#include "Refureku/TypeInfo/DatabaseImpl.inl"
}