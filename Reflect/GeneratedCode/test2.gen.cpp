#include"Src/Reflect/GeneratedCppIncludes.h"
#include"D:\Reflect\ReflectionTest/test\test2.h"
class AAA_TEST_Operator
{
public:
	ConstructRClass(TEST,)
	ConstructRFunction(FUN,TEST,)
};
reflect::RClass*AAA_Construct_RClass_TEST()
{
	return AAA_TEST_Operator::ConstructRClass_TEST(); 
}
reflect::RFunction*AAA_Construct_RFunction_FUN()
{
	return AAA_TEST_Operator::ConstructRFunction_FUN();
}
struct AAA_Construct_TEST_Statics
{
	static RClassConstructor RClass_TEST_Constructor;
	static RFunctionConstructor RFunction_TEST_Constructor[];
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
};
RClassConstructor AAA_Construct_TEST_Statics::RClass_TEST_Constructor = AAA_Construct_RClass_TEST;
RFunctionConstructor AAA_Construct_TEST_Statics::RFunction_TEST_Constructor[]=
{
	AAA_Construct_RFunction_FUN,
};
const uint32_t AAA_Construct_TEST_Statics::FunctionNum = ARRAY_COUNT(AAA_Construct_TEST_Statics::RFunction_TEST_Constructor);
const uint32_t AAA_Construct_TEST_Statics::PropertyNum = 0;
static RegistrationInfo Collector_TEST=
{
	AAA_Construct_TEST_Statics::RClass_TEST_Constructor,
	AAA_Construct_TEST_Statics::RFunction_TEST_Constructor,
	nullptr,
	AAA_Construct_TEST_Statics::FunctionNum,
	AAA_Construct_TEST_Statics::PropertyNum
};
static CollectRegistrationInfo Register (Collector_TEST);
