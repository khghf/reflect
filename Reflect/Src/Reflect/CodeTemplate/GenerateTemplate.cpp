//生成代码的示例模板没什么用
#include<Src/Reflect/GeneratedCppIncludes.h>
using namespace reflect;

class AAA_XXX_Operator
{
public:
	ConstructRClass(TestClass,)
	ConstructRFunction(fun, TestClass,)
	ConstructRProperty(a, TestClass,)
};
RClass* AAA_Construct_RClass_XXX()
{
	return AAA_XXX_Operator::ConstructRClass_TestClass();
}
RFunction* AAA_Construct_RFunction_XXX()
{
	return AAA_XXX_Operator::ConstructRFunction_fun();
}
RProperty* AAA_Construct_RProperty_XXX()
{
	return AAA_XXX_Operator::ConstructRProperty_a();
}
struct AAA_Construct_XXX_Statics
{
	static RClassConstructor RClass_XXX_Constructor;
	static RFunctionConstructor RFunction_XXX_Constructor[];
	static RPropertyConstructor RProperty_XXX_Constructor[];
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
};
 RClassConstructor AAA_Construct_XXX_Statics::RClass_XXX_Constructor = AAA_Construct_RClass_XXX;
 RFunctionConstructor AAA_Construct_XXX_Statics::RFunction_XXX_Constructor[] =
{
	AAA_Construct_RFunction_XXX,
};
const uint32_t AAA_Construct_XXX_Statics::FunctionNum = ARRAY_COUNT(AAA_Construct_XXX_Statics::RFunction_XXX_Constructor);
 RPropertyConstructor AAA_Construct_XXX_Statics::RProperty_XXX_Constructor[] =
{
	AAA_Construct_RProperty_XXX,
};
const uint32_t AAA_Construct_XXX_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_XXX_Statics::RProperty_XXX_Constructor);
const static RegistrationInfo Register_XXX = {
	AAA_Construct_XXX_Statics::RClass_XXX_Constructor,
	AAA_Construct_XXX_Statics::RFunction_XXX_Constructor,
	AAA_Construct_XXX_Statics::RProperty_XXX_Constructor,
	AAA_Construct_XXX_Statics::FunctionNum,
	AAA_Construct_XXX_Statics::PropertyNum
};
const static CollectRegistrationInfo Collect(Register_XXX) ;

