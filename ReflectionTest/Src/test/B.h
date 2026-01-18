#pragma once
#include<B.gen.h>
#include<vector>
#include<iostream>
#include<Reflect/ReflectMarco.h>
#include "A.h"

class CLASS() B :public DM::DMB::A
{
	REFLECT_BODY()
	FUNCTION()
	void funB() {
		std::cout << "B::funB" << b << std::endl;
	}
private:
	PROPERTY()
		float b;
};

