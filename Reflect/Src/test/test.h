#pragma once
#include"ReflectMarco.h"
#include<vector>
namespace DM
{
	class CLASS()  A
	{
		FUNCTION()
			void funA(int a, float b, std::vector<int>c) {}
	public:
		PROPERTY()
		int a;
	};
}
class CLASS() B:public DM::A
{
	void funB(float b) {}
private:
	float b;
};
class  C
{
	void funC(double c) {}
private:
	double c;
};

class   __attribute__((annotate("reflect_class")))D
{

};