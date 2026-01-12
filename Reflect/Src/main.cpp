#include<iostream>
using namespace std;
#include<Reflect/Reflect.h>
int main(int argc, char* argv[])
{
	reflect::Init();
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}
	return 0;
}


//class Foo {
//public:
//	void Func(int a)const {
//		std::cout << a << std::endl;
//	}
//	std::string str;
//};
//int main() {
//		reflect::AddClass<Foo>("Foo").
//		AddMemberFunction("Func", &Foo::Func).
//		AddMemberVariable("str", &Foo::str);
//	Foo foo;
//
//	auto str = reflect::GetByName("Foo").GetMemberVariable("str");
//	str.SetValue<std::string>(foo, "Hello, world!");
//
//	std::cout << str.GetValue<std::string>(foo) << std::endl;
//
//	reflect::GetByName("Foo").GetMemberFunction("Func").Invoke(foo,1);
//
//	return 0;
//}