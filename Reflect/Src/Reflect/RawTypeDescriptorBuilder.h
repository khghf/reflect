#pragma once
#include"TypeDescriptor .h"
#include"MemberFunction.h"
#include"MemberVariable .h"
#include<memory>
namespace reflect
{
	class RawTypeDescriptorBuilder
	{
	public:
		explicit RawTypeDescriptorBuilder(const std::string& name);
		RawTypeDescriptorBuilder(const RawTypeDescriptorBuilder&) = delete;
		~RawTypeDescriptorBuilder();



		template<class Class, typename Var>
		void AddMemberVariable(const std::string& name, Var Class::* var)
		{
			MemberVariable variable(var);
			variable.m_Name = name;
			m_Desc->m_MemberVars.push_back(variable);
		}

		template<class Class, typename Func>
		void AddMemberFunction(const std::string& name, Func Class::* func)
		{
			MemberFunction function(func);
			function.m_Name = name;
			m_Desc->m_MemberFuncs.push_back(function);
		}

	private:
		std::unique_ptr<TypeDescriptor> m_Desc{ nullptr };
	};
}