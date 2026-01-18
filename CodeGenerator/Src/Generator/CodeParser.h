#pragma once
#include<clang-c/Index.h>
#include<string_view>
#include<vector>
namespace reflect
{
	class CodeParser
	{
	public:
		CodeParser();
		~CodeParser();
		void Parse();
		std::string m_ScanDirectory = "Src/test";
		//获取类所属的命名空间，返回值的顺序是颠倒的
		static std::vector<std::string>GetClassNameSpace(CXCursor classNode);
	private:
		void Parse(const std::string_view& filePath);




		CXIndex m_Index;
	};
}


