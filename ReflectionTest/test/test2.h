#pragma once
#include<../Reflect/GeneratedCode/test2.gen.h>
#include"ReflectMarco.h"
#include<iostream>
class CLASS() TEST
{
	REFLECT_BODY();
	FUNCTION()
	void FUN()
	{
		std::cout << "BBBBBBBBBB\n";
	}
public:
	int a, b, c;
};
