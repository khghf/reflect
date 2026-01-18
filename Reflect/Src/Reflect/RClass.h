#pragma once
#include"RObject.h"
#include<unordered_map>
#include"RFunction.h"
#include"RProperty.h"
#include<iostream>
namespace reflect
{
	class RClass:public RObject
	{
		friend class RObjectSetter;
	public:

		RFunction* GetRFunction(const std::string& funName)const 
		{ 
			const auto& it = _Functions.find(funName);
			return it != _Functions.end() ? it->second : nullptr; 
		}
		RProperty* GetRProperty(const std::string& proName)const	
		{ 
			const auto& it = _Properties.find(proName);
			return it != _Properties.end() ? it->second : nullptr;
		}
		template<typename VarType,typename Class>
		VarType GetVariable(const std::string& name,Class& obj)
		{
			RProperty* pro = GetRProperty(name);
			if (pro)return pro->GetValue<VarType>(obj);
			std::cerr << "no variable:" + name + "in class:" + _Name << std::endl;
			return VarType{};
		}
		template<typename VarType, typename Class>
		void SetVariable(const std::string& name, Class& obj, VarType&&var)
		{
			RProperty* pro = GetRProperty(name);
			if (pro) { pro->SetValue<VarType>(obj, std::forward<VarType>(var)); return; };
			std::cerr << "no variable:" + name + "in class:" + _Name << std::endl;
		}
		template<typename Class,typename...Args>
		inline std::any InvokeFun(const std::string& funName,Class&obj,Args...arg)
		{
			RFunction* fun = GetRFunction(funName);
			if(fun)return fun->Invoke(obj, std::forward<Args>(arg)...);
			std::cerr << "no function:" + funName + "in class:" + _Name << std::endl;
			return std::any{};
		}
	private:
		std::vector<RClass*>_SuperClasses;
		std::unordered_map<std::string_view, RFunction*>_Functions;
		std::unordered_map<std::string_view, RProperty*>_Properties;
	};


}