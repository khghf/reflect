#pragma once
#include<A.gen.h>
#include<Reflect/ReflectMarco.h>
#include<iostream>
#include<vector>
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
			int b;
		public:
			PROPERTY()
				int a;
			PROPERTY()
				std::vector<int>arr;
		};
	}
};
