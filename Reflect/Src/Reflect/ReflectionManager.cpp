#include "ReflectionManager.h"
#include<unordered_map>
#include<string>
inline std::unordered_map<size_t, reflect::RClass*>& GetClasses()
{
	static std::unordered_map<size_t, reflect::RClass*>Classes;
	return Classes;
}

void RegisterRegistrationInfo(const RegistrationInfo& Info)
{
	reflect::RClass* rclass = Info.Class();
	GetClasses()[rclass->GetHashCode()] = rclass;
	for (uint32_t i = 0; i < Info.SuperClassNum;++i)
	{
		reflect::RClass* superClass = Info.SuperClasses[i]();
		if (i == 0)
		{
			reflect::RObjectSetter::SetSuperClass(rclass, superClass);
		}
		reflect::RObjectSetter::AddSuperClass(rclass, superClass);
	}
	for (uint32_t i = 0; i < Info.FunctionNum; ++i)
	{
		reflect::RFunction* rfunction = Info.Functions[i]();
		reflect::RObjectSetter::AddRFunToRClass(rclass, rfunction);
		reflect::RObjectSetter::SetSuperClass(rfunction, rclass);
	}
	for (uint32_t i = 0; i < Info.PropertyNum; ++i)
	{
		reflect::RProperty* rproperty = Info.Properties[i]();
		reflect::RObjectSetter::AddRProToRClass(rclass, rproperty);
		reflect::RObjectSetter::SetSuperClass(rproperty, rclass);
	}
}

reflect::RClass* GetRClass(const size_t& hashCode)
{
	const auto& it = GetClasses().find(hashCode);
	if (it != GetClasses().end())return it->second;
	return nullptr;
}

reflect::RFunction* GetRFunction(const size_t& hashCode, const std::string functionName)
{
	const  reflect::RClass* Class = GetRClass(hashCode);
	if (Class)return Class->GetRFunction(functionName);
	return nullptr;
}

reflect::RProperty* GetRProperty(const size_t& hashCode, const std::string propertyName)
{
	const  reflect::RClass* Class = GetRClass(hashCode);
	if (Class)return Class->GetRProperty(propertyName);
	return nullptr;
}
