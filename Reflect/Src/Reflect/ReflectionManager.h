#pragma once
#include "ReflectMarco.h"
#include"RClass.h"
#include"RFunction.h"
#include"RProperty.h"
#include<iostream>

#define TOSTR(x)#x


using RClassConstructor = reflect::RClass * (*)();
using RFunctionConstructor = reflect::RFunction * (*)();
using RPropertyConstructor = reflect::RProperty * (*)();
struct RegistrationInfo
{

	RClassConstructor*SuperClasses;
	RClassConstructor Class;
	RFunctionConstructor*Functions;
	RPropertyConstructor*Properties;
	const  uint32_t SuperClassNum;
	const  uint32_t FunctionNum;
	const  uint32_t PropertyNum;
};
//配合RegisterRegistrationInfo在dll导入初始化静态变量时注册
struct  CollectRegistrationInfo
{
	template<typename...Args>
	CollectRegistrationInfo(Args&&...arg)
	{
		std::cout << "Collect info" << std::endl;
		RegisterRegistrationInfo(std::forward<Args>(arg)...);
	}
};
//注册收集到的信息，生成RClass,RFunction.....
void RegisterRegistrationInfo(const RegistrationInfo& Info);
Reflect_API reflect::RClass* GetRClass(const size_t& hashCode);
Reflect_API reflect::RFunction* GetRFunction(const size_t& hashCode, const std::string functionName);
Reflect_API reflect::RProperty* GetRProperty(const size_t& hashCode, const std::string propertyName);
namespace reflect
{
	class RObjectSetter
	{
	public:
		static void SetName(reflect::RObject* obj, const std::string& val) { obj->_Name = val; }
		static void SetHashCode(reflect::RObject* obj, const size_t& val) { obj->_HashCode = val; }
		static void SetSuperClass(reflect::RObject* obj, reflect::RClass* val) { obj->_SuperClass = val; }
		static void AddRFunToRClass(reflect::RClass* obj, reflect::RFunction* val) { obj->_Functions[val->_Name] = val; }
		static void AddRProToRClass(reflect::RClass* obj, reflect::RProperty* val) { obj->_Properties[val->_Name] = val; }
		static bool IsAlreadyConstruct(reflect::RObject* obj) { return !obj->_Name.empty(); }
		static void AddSuperClass(reflect::RClass* obj, reflect::RClass* val) { obj->_SuperClasses.emplace_back(val); }

	};
	class Reflect_API ReflectionManager
	{
	public:
		template<typename Class>
		static RClass* GetRClass() { return ::GetRClass(typeid(Class).hash_code()); }
		template<typename Class>
		static  RFunction* GetRFunction(const std::string& functionName) { return GetRFunction(typeid(Class).hash_code(), functionName); }
		template<typename Class>
		static  RProperty* GetRProperty(const std::string& propertyName) { return GetRProperty(typeid(Class).hash_code(), propertyName); }
	};
}