#include "ReflectionManager.h"
#include<unordered_map>
#include<string>
inline std::unordered_map<std::string, reflect::RClass*>& GetClasses()
{
	static std::unordered_map<std::string, reflect::RClass*>Classes;
	return Classes;
}
namespace reflect
{
	RClass* ReflectionManager::GetRClass(const std::string& name)
	{
		const auto& it = GetClasses().find(name);
		if (it != GetClasses().end())return it->second;
		return nullptr;
	}

	RFunction* ReflectionManager::GetRFunction(const std::string& className, const std::string& functionName)
	{
		const  RClass* Class = GetRClass(className);
		if (Class)return Class->GetFunction(functionName);
		return nullptr;
	}

	RProperty* ReflectionManager::GetRProperty(const std::string& className, const std::string& propertyName)
	{
		const  RClass* Class = GetRClass(className);
		if (Class)return Class->GetProperty(propertyName);
		return nullptr;
	}
}

void RegisterRegistrationInfo(const RegistrationInfo& Info)
{
	reflect::RClass* rclass = Info.Class();
	GetClasses()[rclass->GetName()] = rclass;
	
	for (uint32_t i = 0; i < Info.FunctionNum; ++i)
	{
		reflect::RFunction* rfunction = Info.Functions[i]();
		reflect::RObjectSetter::AddRFunToRClass(rclass, rfunction);
	}
	for (uint32_t i = 0; i < Info.PropertyNum; ++i)
	{
		reflect::RProperty* rproperty = Info.Properties[i]();
		reflect::RObjectSetter::AddRProToRClass(rclass, rproperty);
	}
}

