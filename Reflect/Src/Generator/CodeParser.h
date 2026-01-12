#pragma once

//#ifdef _MSC_VER // 仅对 MSVC 编译器生效
//#pragma warning(push) // 保存当前警告状态
//#pragma warning(disable: 4996) // 屏蔽 C4996 错误
//#endif
#include<clang-c/Index.h>
#include<string_view>
namespace reflect
{
	class CodeParser
	{
	public:
		CodeParser();
		~CodeParser();
		void Parse();
	private:
		void Parse(const std::string_view& fileName);
		CXIndex m_Index;
		std::string_view m_ScanDirectory = "Src/test";
	};
}


