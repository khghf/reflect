#pragma once
#include "../ReflectMarco.h"
#include"RClass.h"
#include"RFunction.h"
#include"RProperty.h"
#include<iostream>
namespace reflect
{
	class RObjectSetter
	{
	public:
		static void SetName(reflect::RObject* obj, const std::string& val) { obj->_Name = val; }
		static void SetSuperClass(reflect::RObject* obj, reflect::RClass* val) { obj->_SuperClass = val; }
		static void AddRFunToRClass(reflect::RClass* obj, reflect::RFunction* val) { obj->_Functions[val->_Name] = val; }
		static void AddRProToRClass(reflect::RClass* obj, reflect::RProperty* val) { obj->_Properties[val->_Name] = val; }
	};
	class Reflect_API ReflectionManager
	{
	public:
		static  RClass *	GetRClass(const std::string& name);
		static  RFunction * GetRFunction(const std::string& className, const std::string& functionName);
		static  RProperty * GetRProperty(const std::string& className, const std::string& propertyName);
	};
}
using RClassConstructor = reflect::RClass * (*)();
using RFunctionConstructor = reflect::RFunction * (*)();
using RPropertyConstructor = reflect::RProperty * (*)();
struct RegistrationInfo
{
	 RClassConstructor Class;
	 RFunctionConstructor*Functions;
	 RPropertyConstructor*Properties;
	const  uint32_t FunctionNum;
	const  uint32_t PropertyNum;
};
//配合RegisterRegistrationInfo在dll导入初始化静态变量时注册
struct Reflect_API CollectRegistrationInfo
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
#include<iostream>
class TestClass
{
	friend class AAA_XXX_Operator;
public:
	TestClass() = default;
	~TestClass() = default;
	void fun() {
		std::cout << "TestClass::fun()\n";
	}
private:
	int a;
};
