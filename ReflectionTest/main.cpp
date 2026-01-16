
#include<Src/Reflect/ReflectionManager.h>
#include"test/test.h"
#include"test/test2.h"
int main()
{
	DM::DMB::A test;
	TEST test2;
	reflect::RClass* rclass = reflect::ReflectionManager::GetRClass("A");
	reflect::RFunction* rfun = rclass->GetFunction("funA");
	rfun->Invoke(test,1,1.f);
	reflect::ReflectionManager::GetRClass("TEST")->GetFunction("FUN")->Invoke(test2);
	std::cout << "Main\n";
	return 0;
}