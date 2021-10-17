/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Refureku/Object.h>
#include <Refureku/NativeProperties.h>

#include "TestClass.h"

#include "Generated/BaseObject.rfkh.h"

class CLASS() BaseObject : public rfk::Object
{
	private:
		FIELD()
		int _i;

		METHOD(Instantiator)
		static BaseObject* customInstantiator(int i) noexcept
		{
			return new BaseObject(i);
		}

	public:
		BaseObject(int i) noexcept:
			_i{i}
		{
		}

		METHOD()
		int getI() const noexcept
		{
			return _i;
		}

	BaseObject_GENERATED
};

class CLASS() ObjectDerived1 : public BaseObject
{
	private:
		METHOD(Instantiator)
		static ObjectDerived1* customInstantiator() noexcept
		{
			return new ObjectDerived1(1);
		}

	public:
		using BaseObject::BaseObject;

	ObjectDerived1_GENERATED
};

class CLASS() ObjectDerived2 : public BaseObject
{
	public:
		ObjectDerived2() noexcept:
			BaseObject(2)
		{
		}

	ObjectDerived2_GENERATED
};

class CLASS() ObjectDerivedDerived : public ObjectDerived1
{
	ObjectDerivedDerived_GENERATED
};

class CLASS() MultipleInheritanceClass : public ObjectDerived2, public TestClass
{
	MultipleInheritanceClass_GENERATED
};

File_BaseObject_GENERATED