#include<Reflect/GeneratedCppIncludes.h>
#include"D:\Reflection\ReflectionTest/Src/test\A.h"
class AAA_A_Operator
{
public:
	ConstructRClass(A,DM::DMB)
	ConstructRFunction(funA,A,DM::DMB)
	ConstructRProperty(a,A,DM::DMB)
	ConstructRProperty(arr,A,DM::DMB)
};
reflect::RClass*AAA_Construct_RClass_A()
{
	return AAA_A_Operator::ConstructRClass_A(); 
}
reflect::RFunction*AAA_Construct_RFunction_funA()
{
	return AAA_A_Operator::ConstructRFunction_funA();
}
reflect::RProperty*AAA_Construct_RProperty_a()
{
	return AAA_A_Operator::ConstructRProperty_a();
}
reflect::RProperty*AAA_Construct_RProperty_arr()
{
	return AAA_A_Operator::ConstructRProperty_arr();
}
struct AAA_Construct_A_Statics
{
	static RClassConstructor RClass_A_Constructor;
	static RFunctionConstructor RFunction_A_Constructor[];
	static RPropertyConstructor RProperty_A_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
};
RClassConstructor AAA_Construct_A_Statics::RClass_A_Constructor = AAA_Construct_RClass_A;
RFunctionConstructor AAA_Construct_A_Statics::RFunction_A_Constructor[]=
{
	AAA_Construct_RFunction_funA,
};
RPropertyConstructor AAA_Construct_A_Statics::RProperty_A_Constructor[]=
{
	AAA_Construct_RProperty_a,
	AAA_Construct_RProperty_arr,
};
const uint32_t AAA_Construct_A_Statics::SuperClassNum = 0;
const uint32_t AAA_Construct_A_Statics::FunctionNum = ARRAY_COUNT(AAA_Construct_A_Statics::RFunction_A_Constructor);
const uint32_t AAA_Construct_A_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_A_Statics::RProperty_A_Constructor);
static RegistrationInfo Collector_A=
{
	nullptr,
	AAA_Construct_A_Statics::RClass_A_Constructor,
	AAA_Construct_A_Statics::RFunction_A_Constructor,
	AAA_Construct_A_Statics::RProperty_A_Constructor,
	AAA_Construct_A_Statics::SuperClassNum,
	AAA_Construct_A_Statics::FunctionNum,
	AAA_Construct_A_Statics::PropertyNum
};
static CollectRegistrationInfo Register_A(Collector_A); 
