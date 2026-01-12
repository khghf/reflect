#pragma once


#define TOSTRING(x) #x; 
#include"RawTypeDescriptorBuilder.h"
namespace reflect
{
	template<class Class>
	class TypeDescriptorBuilder
	{
	public:
		explicit TypeDescriptorBuilder(const std::string& name) : m_RawBuilder(name) {}

		template<typename Var>
		TypeDescriptorBuilder& AddMemberVariable(const std::string& name, Var Class::* var)
		{
			m_RawBuilder.AddMemberVariable(name, var);
			return *this;
		}
		template<typename Func>
		TypeDescriptorBuilder& AddMemberFunction(const std::string& name, Func Class::* func)
		{
			m_RawBuilder.AddMemberFunction(name, func);
			return *this;
		}

	private:
		RawTypeDescriptorBuilder m_RawBuilder;
	};
}

