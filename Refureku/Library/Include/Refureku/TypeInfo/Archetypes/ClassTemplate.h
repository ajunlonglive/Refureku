/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <unordered_set>
#include <array>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.h"

namespace rfk
{
	//Forward declaration
	class TemplateParameter;

	class ClassTemplate : public Class
	{
		private:
			/** List of all template parameters of this class template. */
			std::vector<TemplateParameter const*>			_templateParameters;

			/** All different instantiations of this class template in the program (with different template parameters). */
			std::vector<ClassTemplateInstantiation const*>	_instantiations;

		public:
			REFUREKU_API ClassTemplate(std::string&&	name,
									   std::size_t		id,
									   bool				isClass)	noexcept;

			/**
			*	@brief Get the instance corresponding to the provided template arguments if it exists in the program.
			* 
			*	@return The instance if any, else nullptr.
			*/
			template <typename... Types>
			ClassTemplateInstantiation const*	getInstantiation()															const	noexcept;

			/**
			*	@brief Get the instance corresponding to the provided template arguments if it exists in the program.
			* 
			*	@return The instance if any, else nullptr.
			*/
			template <std::size_t ArraySize>
			ClassTemplateInstantiation const*	getInstantiation(std::array<Archetype const*, ArraySize> const& archetypes)	const	noexcept;	//TODO: Should be an array of TemplateArgument instead

			/**
			*	@brief Add a template parameter.
			* 
			*	@param templateParameter The template parameter to add.
			*/
			REFUREKU_API void								addTemplateParameter(TemplateParameter const& templateParameter)		noexcept;

			/**
			*	@brief Register an instance generated from this class template.
			* 
			*	@param inst The instantiation to register.
			*/
			REFUREKU_API void								registerClassTemplateInstantiation(ClassTemplateInstantiation& inst)	noexcept;

			/**
			*	@brief Get the template parameter at the specified index.
			*
			*	@return The template parameter at the specified index.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of template parameters.
			*/
			REFUREKU_API TemplateParameter const&			getTemplateParameter(std::size_t parameterIndex)				const;

			/**
			*	@brief Get the number of template parameters for this class template.
			*
			*	@return The number of template parameters for this class template.
			*/
			REFUREKU_API std::size_t						getTemplateParametersCount()									const	noexcept;

			/**
			*	@brief Get the instantiation stored at index.
			*
			*	@return The instance at the specified index.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of registered instances.
			*/
			REFUREKU_API ClassTemplateInstantiation const&	getInstantiation(std::size_t instanceIndex)						const;

			/**
			*	@brief Get the number of instantiations (with different template parameters) of this class template within the program.
			* 
			*	@return The number of instantiations of this class template within the program.
			*/
			REFUREKU_API std::size_t						getInstantiationsCount()										const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/ClassTemplate.inl"
}