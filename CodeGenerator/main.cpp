#include"Src/Generator/CodeParser.h"
#include"Src/Generator/CodeGrenerator.h"
#include<iostream>
int main(int args, char* argment[])
{
	reflect::CodeParser parse;
	parse.m_ScanDirectory = "D:/Reflect/ReflectionTest/test";
	if(args>=2)parse.m_ScanDirectory = argment[1];
	parse.Parse();
	for (int i = 0; i < args; ++i)
	{
		std::cout <<"Argment:"<<argment[i] << std::endl;
	}
	reflect::CodeGrenerator::FileStorageFloder = "../Reflect/GeneratedCode";
	reflect::CodeGrenerator::GenerateCode();
	return 0;
}