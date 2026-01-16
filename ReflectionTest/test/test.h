#pragma once
#include<../Reflect/GeneratedCode/test.gen.h>
#include<vector>
#include<iostream>
#include<ReflectMarco.h>
namespace DM
{
	namespace DMB
	{
		class CLASS()A
		{
			REFLECT_BODY()
			FUNCTION()
			void funA(int a, float b) 
			{
				std::cout << a + b << std::endl;
			}
		public:
			PROPERTY()
				int a;
		};
	}
};

class B:public DM::DMB::A
{
	void funB(float b) {}
private:
	float b;
};

class C
{
	void funC(double c) {}
private:
	double c;
};


class D
{

};

