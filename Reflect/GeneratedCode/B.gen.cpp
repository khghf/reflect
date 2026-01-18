#include<Reflect/GeneratedCppIncludes.h>
#include"D:\Reflection\ReflectionTest/Src/test\B.h"
class AAA_B_Operator
{
public:
	ConstructRClass(B,)
	ConstructRFunction(funB,B,)
	ConstructRProperty(b,B,)
};
extern reflect::RClass*AAA_Construct_RClass_A();
reflect::RClass*AAA_Construct_RClass_B()
{
	return AAA_B_Operator::ConstructRClass_B(); 
}
reflect::RFunction*AAA_Construct_RFunction_funB()
{
	return AAA_B_Operator::ConstructRFunction_funB();
}
reflect::RProperty*AAA_Construct_RProperty_b()
{
	return AAA_B_Operator::ConstructRProperty_b();
}
struct AAA_Construct_B_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_B_Constructor;
	static RFunctionConstructor RFunction_B_Constructor[];
	static RPropertyConstructor RProperty_B_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
};
RClassConstructor AAA_Construct_B_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_A,
};
RClassConstructor AAA_Construct_B_Statics::RClass_B_Constructor = AAA_Construct_RClass_B;
RFunctionConstructor AAA_Construct_B_Statics::RFunction_B_Constructor[]=
{
	AAA_Construct_RFunction_funB,
};
RPropertyConstructor AAA_Construct_B_Statics::RProperty_B_Constructor[]=
{
	AAA_Construct_RProperty_b,
};
const uint32_t AAA_Construct_B_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_B_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_B_Statics::FunctionNum = ARRAY_COUNT(AAA_Construct_B_Statics::RFunction_B_Constructor);
const uint32_t AAA_Construct_B_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_B_Statics::RProperty_B_Constructor);
static RegistrationInfo Collector_B=
{
	AAA_Construct_B_Statics::SuperClass_Constructor,
	AAA_Construct_B_Statics::RClass_B_Constructor,
	AAA_Construct_B_Statics::RFunction_B_Constructor,
	AAA_Construct_B_Statics::RProperty_B_Constructor,
	AAA_Construct_B_Statics::SuperClassNum,
	AAA_Construct_B_Statics::FunctionNum,
	AAA_Construct_B_Statics::PropertyNum
};
static CollectRegistrationInfo Register_B(Collector_B); 
