#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

//#include "RefurekuGenerator/CodeGen/GeneratedEntityCodeTemplate.h"	//generateNativePropertiesCode

using namespace rfk;

ReflectionCodeGenModule::ReflectionCodeGenModule() noexcept
{
	addPropertyCodeGen(_customInstantiatorProperty);
	addPropertyCodeGen(_propertySettingsProperty);
}

ReflectionCodeGenModule::ReflectionCodeGenModule(ReflectionCodeGenModule const&) noexcept:
	ReflectionCodeGenModule()
{
}

ReflectionCodeGenModule* ReflectionCodeGenModule::clone() const noexcept
{
	return new ReflectionCodeGenModule(*this);
}

bool ReflectionCodeGenModule::preGenerateCode(kodgen::EntityInfo const* entity, kodgen::MacroCodeGenEnv& env) noexcept
{
	//env.getLogger()->log(env.getFileParsingResult()->parsedFile.string() + ": " + entity->name);

	return true;
}

//std::string const				ReflectionCodeGenModule::_nativePropsMacroName	= std::string(_internalPrefix) + "NativeProperties_GENERATED";
//std::hash<std::string> const	ReflectionCodeGenModule::_stringHasher;

//void FileGenerationUnit::postGenerateFile(kodgen::FileParsingResult const& /* parsingResult */) noexcept
//{
//	_generatedNamespaces.clear();
//	_generatedClasses.clear();
//	_generatedEnums.clear();
//	_generatedVariables.clear();
//	_generatedFunctions.clear();
//
//	_entitiesUsingNativeProperties.clear();
//}
//
//std::string FileGenerationUnit::getEndFileMacroName() const noexcept
//{
//	return "File_GENERATED";
//}
//
//void FileGenerationUnit::writeHeader(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
//{
//	//Always call base class
//	kodgen::FileGenerationUnit::writeHeader(file, parsingResult);
//
//	file.writeLines("#include <Refureku/Misc/DisableWarningMacros.h>",
//					"#include <Refureku/TypeInfo/Namespaces/Namespace.h>",
//					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragment.h>",
//					"#include <Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h>",
//					"#include <Refureku/TypeInfo/Archetypes/Class.h>",
//					"#include <Refureku/TypeInfo/Archetypes/Enum.h>",
//					"#include <Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h>",
//					"#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>",
//					"\n");
//}
//
//void FileGenerationUnit::writeFooter(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& parsingResult) const noexcept
//{
//	//Always call base class
//	kodgen::FileGenerationUnit::writeFooter(file, parsingResult);
//
//	file.undefMacro(_nativePropsMacroName);
//	generateNativePropertiesCode(file, parsingResult);
//
//	file.undefMacro(getEndFileMacroName());
//	generateEndFileMacro(file);
//}
//
//bool FileGenerationUnit::writeEntityToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& entityInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& out_genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeEntityToFile(generatedFile, entityInfo, parsingResult, out_genResult))
//	{
//		saveEntitiesUsingNativeProperties(entityInfo);
//
//		return true;
//	}
//
//	return false;
//}
//
//bool FileGenerationUnit::writeNamespaceToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& namespaceInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeNamespaceToFile(generatedFile, namespaceInfo, parsingResult, genResult))
//	{
//		_generatedNamespaces.push_back(reinterpret_cast<kodgen::NamespaceInfo const*>(&namespaceInfo));
//
//		return true;
//	}
//
//	return false;
//}
//
//bool FileGenerationUnit::writeStructOrClassToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& structClassInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeStructOrClassToFile(generatedFile, structClassInfo, parsingResult, genResult))
//	{
//		_generatedClasses.push_back(reinterpret_cast<kodgen::StructClassInfo const*>(&structClassInfo));
//
//		return true;
//	}
//
//	return false;
//}
//
//bool FileGenerationUnit::writeEnumToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& enumInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeEnumToFile(generatedFile, enumInfo, parsingResult, genResult))
//	{
//		_generatedEnums.push_back(reinterpret_cast<kodgen::EnumInfo const*>(&enumInfo));
//
//		return true;
//	}
//
//	return false;
//}
//
//bool FileGenerationUnit::writeVariableToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& variableInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeVariableToFile(generatedFile, variableInfo, parsingResult, genResult))
//	{
//		_generatedVariables.push_back(reinterpret_cast<kodgen::VariableInfo const*>(&variableInfo));
//
//		return true;
//	}
//
//	return false;
//}
//
//bool FileGenerationUnit::writeFunctionToFile(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo& functionInfo, kodgen::FileParsingResult const& parsingResult, kodgen::FileGenerationResult& genResult) noexcept
//{
//	if (kodgen::FileGenerationUnit::writeFunctionToFile(generatedFile, functionInfo, parsingResult, genResult))
//	{
//		_generatedFunctions.push_back(reinterpret_cast<kodgen::FunctionInfo const*>(&functionInfo));
//
//		return true;
//	}
//
//	return false;
//}
//
//void FileGenerationUnit::generateEndFileMacro(kodgen::GeneratedFile& file) const noexcept
//{
//	file.writeLine("#define " + getEndFileMacroName() + "\t\\");
//
//	//Enum first because structs/classes and namespaces can have nested (and then reference to) enums
//	for (kodgen::EnumInfo const* enumInfo : _generatedEnums)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(enumInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Gen variables
//	for (kodgen::VariableInfo const* varInfo : _generatedVariables)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(varInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Gen functions
//	for (kodgen::FunctionInfo const* funcInfo : _generatedFunctions)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(funcInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Structs/Classes before namespaces because namespaces can have nested (and then reference to) structs/classes
//	for (kodgen::StructClassInfo const* classInfo : _generatedClasses)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(classInfo->id)) + "u_GetTypeDefinition\t\\");
//	}
//
//	for (kodgen::NamespaceInfo const* namespaceInfo : _generatedNamespaces)
//	{
//		file.writeLine("	" + std::string(_internalPrefix) + std::to_string(_stringHasher(namespaceInfo->id)) + "u_GENERATED\t\\");
//	}
//
//	//Native properties footer code
//	file.writeLine("	" + _nativePropsMacroName + "\t\\");
//
//	//New line to avoid "warning: backslash-newline at end of file"
//	file.writeLine("\n");
//}
//
//void FileGenerationUnit::saveEntitiesUsingNativeProperties(kodgen::EntityInfo const& entityInfo) noexcept
//{
//	for (kodgen::SimpleProperty const& prop : entityInfo.properties.simpleProperties)
//	{
//		if (prop.boundPropertyRule != nullptr)
//		{
//			_entitiesUsingNativeProperties.push_back(&entityInfo);
//			return;
//		}
//	}
//
//	for (kodgen::ComplexProperty const& prop : entityInfo.properties.complexProperties)
//	{
//		if (prop.boundPropertyRule != nullptr)
//		{
//			_entitiesUsingNativeProperties.push_back(&entityInfo);
//			return;
//		}
//	}
//}
//
//void FileGenerationUnit::generateNativePropertiesCode(kodgen::GeneratedFile& file, kodgen::FileParsingResult const& /* parsingResult */) const noexcept
//{
//	std::string generatedCode;
//
//	//Generate native properties header code
//	PropertyCodeGenFileHeaderData headerData;
//	
//	for (kodgen::EntityInfo const* entityInfo : _entitiesUsingNativeProperties)
//	{
//		assert(entityInfo != nullptr);
//
//		generatedCode += GeneratedEntityCodeTemplate::generateNativePropertiesCode(*entityInfo, &headerData);
//	}
//
//	file.writeLine(generatedCode);
//
//	//Generate native properties footer code inside a macro
//	PropertyCodeGenFileFooterData footerData;
//
//	generatedCode.clear();
//	for (kodgen::EntityInfo const* entityInfo : _entitiesUsingNativeProperties)
//	{
//		assert(entityInfo != nullptr);
//
//		generatedCode += GeneratedEntityCodeTemplate::generateNativePropertiesCode(*entityInfo, &footerData);
//	}
//
//	file.writeMacro(std::string(_nativePropsMacroName), std::move(generatedCode));
//}