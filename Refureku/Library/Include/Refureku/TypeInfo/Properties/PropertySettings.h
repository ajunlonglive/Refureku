/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Properties/Property.h"

#include "Refureku/Generated/PropertySettings.rfk.h"

/**
*	@brief Property used to define basic settings of a property. Can't be used on structs or classes not inheriting from rfk::Property.
*/
struct RFKStruct(PropertySettings(rfk::EEntityKind::Struct | rfk::EEntityKind::Class)) PropertySettings : public rfk::Property
{
	public:
		/**
		*	@param targetEntityKind_	Kind of entities the property can be attached to. Use the | operator to specify multiple entity kinds.
		*	@param allowMultiple_		Is this property allowed to be attached multiple times to the same entity?
		*	@param shouldInherit_		Should this property be inherited by children when used on structs/classes or virtual methods.
		*/
		PropertySettings(rfk::EEntityKind		_targetEntityKind_ [[maybe_unused]],		//first [[maybe_unused]] is written after the variable name for pre-gcc 9.3 compatibility
						 [[maybe_unused]] bool	_allowMultiple_ = false,
						 [[maybe_unused]] bool	_shouldInherit_ = true)	noexcept
		{
		}

	PropertySettings_GENERATED
};

File_GENERATED