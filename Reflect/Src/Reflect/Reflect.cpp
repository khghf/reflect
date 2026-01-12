#include"Reflect.h"
#include<Generator/CodeParser.h>
#include<Generator/CodeGrenerator.h>
#include<Meta/MetaInfo.h>
namespace reflect
{
	void Init()
	{
		reflect::CodeParser pase;
		pase.Parse();
		CodeGrenerator::GenerateCode();
		MetaInfo::ClearMetaInfo();
	}

}