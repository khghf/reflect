#pragma once
#include<string>
#include<vector>
#include"MemberVariable .h"
#include"MemberFunction.h"
namespace reflect
{
	class TypeDescriptor 
	{
		friend class RawTypeDescriptorBuilder;
	public:
		const std::string&					GetName()const				{ return m_Name; }
		const std::vector<MemberVariable>&	GetMemberVariables() const	{ return m_MemberVars; }
		const std::vector<MemberFunction>&	GetMemberFunctions() const	{ return m_MemberFuncs; }
		
		MemberVariable GetMemberVariable(const std::string& name) const 
		{
			for (auto& var : m_MemberVars)
			{
				if (var.GetName() == name)return var;
			}
			return MemberVariable{};
		}

		MemberFunction GetMemberFunction(const std::string& name) const 
		{
			for (auto& func : m_MemberFuncs)
			{
				if (func.GetName() == name)return func;
			}
			return MemberFunction{};
		}
	private:
		std::string m_Name;
		std::vector<MemberVariable> m_MemberVars;
		std::vector<MemberFunction> m_MemberFuncs;
	};
}