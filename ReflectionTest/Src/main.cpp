#include"Src/Reflect/ReflectionManager.h"
#include"test/A.h"
#include"test/B.h"
int main()
{
	DM::DMB::A a;
	B b;
	{
		reflect::RClass* rclass = reflect::ReflectionManager::GetRClass<DM::DMB::A>();
		reflect::RFunction* rfun = rclass->GetRFunction("funA");
		rfun->Invoke(a, 1, 1.f);
		rclass->InvokeFun("funA", a, 4, 4.f);
		std::vector<int>arr = { 1,2,3,4,5,6,7,8,9 };
		rclass->SetVariable("arr", a, arr);
		int i = 5;
		while (i--)
		{
			arr.push_back(2);
			rclass->SetVariable("arr", a, arr);
			for (const auto& var : rclass->GetVariable<std::vector<int>>("arr", a))
			{
				
				std::cout << var << std::endl;
			}
		}
		
	}
	{
		reflect::RClass* rclass = reflect::ReflectionManager::GetRClass<B>();
		reflect::RFunction* rfun = rclass->GetRFunction("funB");
		reflect::RProperty* rpro = rclass->GetRProperty("b");
		rpro->SetValue<float>(b, 10000);
		rfun->Invoke(b);

		rclass->SetVariable("b", b, 200.f);
		rclass->InvokeFun("funB", b);
		std::cout << rclass->GetVariable<float>("b", b) << std:: endl;
	}
	
	std::cout << "Main\n";
	return 0;
}