#pragma once
#include"TypeDescriptorBuilder.h"
#include"ReflectInfoRegistry .h"
namespace reflect
{
	void Init();
	template<class Class>
	inline TypeDescriptorBuilder<Class> AddClass(const std::string& name)
	{
		return TypeDescriptorBuilder<Class>(name);
	}
	inline std::vector<TypeDescriptor*> Get()
	{
		return ReflectInfoRegistry::Instance().Get();
	}
	inline TypeDescriptor& GetByName(const std::string& name)
	{
		return *ReflectInfoRegistry::Instance().Find(name);
	}
}