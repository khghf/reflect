#pragma once
#include"RObject.h"
#include<unordered_map>
#include"RFunction.h"
#include"RProperty.h"
namespace reflect
{
	class RClass:public RObject
	{
		friend class RObjectSetter;
	public:
		RFunction* GetFunction(const std::string& funName)const 
		{ 
			const auto& it = _Functions.find(funName);
			return it != _Functions.end() ? it->second : nullptr; 
		}
		RProperty* GetProperty(const std::string& proName)const	
		{ 
			const auto& it = _Properties.find(proName);
			return it != _Properties.end() ? it->second : nullptr;
		}
	private:
		std::vector<RClass*>_SuperClasses;
		std::unordered_map<std::string_view, RFunction*>_Functions;
		std::unordered_map<std::string_view, RProperty*>_Properties;
	};


}