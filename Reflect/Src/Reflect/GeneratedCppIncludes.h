#pragma once
#include"ReflectionManager.h"
#include<typeindex>
#define ARRAY_COUNT(x)sizeof(x)/sizeof(x[0])
#define ConstructRClass(ClassName,nameSpace)\
		static  reflect::RClass* ConstructRClass_##ClassName()\
		{\
			static  reflect::RClass class_##ClassName;\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&class_##ClassName))return &class_##ClassName;\
			reflect::RObjectSetter::SetName(&class_##ClassName, #ClassName);\
			reflect::RObjectSetter::SetHashCode(&class_##ClassName,typeid(nameSpace::ClassName).hash_code());\
			return &class_##ClassName;\
		};

#define ConstructRFunction(FunctionName,SuperClassName,nameSpace)\
		static reflect::RFunction* ConstructRFunction_##FunctionName()\
		{\
			static reflect::RFunction function_##FunctionName(&nameSpace::SuperClassName::FunctionName);\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&function_##FunctionName))return &function_##FunctionName;\
			reflect::RObjectSetter::SetName(&function_##FunctionName, #FunctionName);\
			reflect::RObjectSetter::SetSuperClass(&function_##FunctionName, ConstructRClass_##SuperClassName());\
			return &function_##FunctionName;\
		};

#define ConstructRProperty(PropertyName,SuperClassName,nameSpace)\
		static  reflect::RProperty* ConstructRProperty_##PropertyName()\
		{\
			static  reflect::RProperty property_##PropertyName(&nameSpace::SuperClassName::PropertyName);\
			if(reflect::RObjectSetter::IsAlreadyConstruct(&property_##PropertyName))return &property_##PropertyName;\
			reflect::RObjectSetter::SetName(&property_##PropertyName, #PropertyName);\
			reflect::RObjectSetter::SetSuperClass(&property_##PropertyName, ConstructRClass_##SuperClassName());\
			return &property_##PropertyName;\
		};


