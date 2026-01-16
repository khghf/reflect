#pragma once
#include"ReflectionManager.h"
#define ARRAY_COUNT(x)sizeof(x)/sizeof(x[0])
#define ConstructRClass(ClassName,nameSpace)\
		static  reflect::RClass* ConstructRClass_##ClassName()\
		{\
			static  reflect::RClass class_##ClassName;\
			reflect::RObjectSetter::SetName(&class_##ClassName, #ClassName);\
			return &class_##ClassName;\
		};

#define ConstructRFunction(FunctionName,SuperClassName,nameSpace)\
		static reflect::RFunction* ConstructRFunction_##FunctionName()\
		{\
			static reflect::RFunction function_##FunctionName(&nameSpace::SuperClassName::FunctionName);\
			reflect::RObjectSetter::SetName(&function_##FunctionName, #FunctionName);\
			reflect::RObjectSetter::SetSuperClass(&function_##FunctionName, ConstructRClass_##SuperClassName());\
			return &function_##FunctionName;\
		};

#define ConstructRProperty(PropertyName,SuperClassName,nameSpace)\
		static  reflect::RProperty* ConstructRProperty_##PropertyName()\
		{\
			static  reflect::RProperty property_##PropertyName(&nameSpace::SuperClassName::PropertyName);\
			reflect::RObjectSetter::SetName(&property_##PropertyName, #PropertyName);\
			reflect::RObjectSetter::SetSuperClass(&property_##PropertyName, ConstructRClass_##SuperClassName());\
			return &property_##PropertyName;\
		};


