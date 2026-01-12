#pragma once
namespace reflect
{
	class CodeGrenerator
	{
		friend class CodeParser;
	public:
		static void GenerateCode();
	private:
		static void Generate_h();
		static void Generate_cpp();
	};
}


