#include "CodeParser.h"
#include<iostream>
#include"Util.h"
#include<Meta/MetaInfo.h>
using namespace std;

namespace reflect
{
	struct ParseContext
	{
		CXCursor CurrrentClassNode;
		std::string FileName;
	};
	ParseContext Context;
	static CXChildVisitResult CursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
	static CXChildVisitResult ParseClass(CXCursor classNode);
	static CXChildVisitResult ParseFunction(CXCursor functionNode);
	static CXChildVisitResult ParseProperty(CXCursor propertyNode);




	CodeParser::CodeParser() :m_Index(nullptr)
	{
		m_Index = clang_createIndex(0, 0);
		if (m_Index == nullptr)
		{
			std::cerr << "Create CXIndex failed:" << __FILE__<< std::endl;
			return;
		}
	}

	CodeParser::~CodeParser()
	{
		if (m_Index)clang_disposeIndex(m_Index);
	}


	void CodeParser::Parse()
	{
		std::vector<std::string>filePaths = Util::GetAllFilePath(m_ScanDirectory.data(), true);
		for (const auto& path : filePaths)
		{
			if (Util::GetFileSuffix(path) != "cpp")continue;
			Parse(path);
		}
	}


	void CodeParser::Parse(const std::string_view& fileName)
	{
		CXTranslationUnit unit;
		const char* arguments[] = {
		"c++",
		"-std=c++17",
		"-DENABLE_PARSER"
		};
		int argCount = sizeof(arguments) / sizeof(arguments[0]);
		CXErrorCode errorCode = clang_parseTranslationUnit2(m_Index, fileName.data(), arguments, argCount, nullptr, 0, CXTranslationUnit_None, &unit);
		if (errorCode != CXError_Success)
		{
			switch (errorCode)
			{
			case CXError_Failure:std::cerr << "Create CXTranslationUnit:CXError_Failure" << __FILE__ << std::endl;
				break;
			case CXError_Crashed:std::cerr << "Create CXTranslationUnit:CXError_Crashed" << __FILE__ << std::endl;
				break;
			case CXError_InvalidArguments:std::cerr << "Create CXTranslationUnit:CXError_InvalidArguments" << __FILE__ << std::endl;
				break;
			case CXError_ASTReadError:std::cerr << "Create CXTranslationUnit:CXError_ASTReadError" << __FILE__ << std::endl;
				break;
			default:
				break;
			}
			return;
		}
		Context.FileName = fileName;
		MetaFile meta(fileName.data());
		MetaInfo::RegisterMetaFile(meta);
		CXCursor root = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(root, CursorVisitor, nullptr);
		clang_disposeTranslationUnit(unit);
	}



	CXChildVisitResult CursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
	{
		CXCursorKind c_kind = clang_getCursorKind(cursor);
		if (c_kind == CXCursor_AnnotateAttr)
		{
			std::string attrStr = Util::DisplayName(cursor);

			if (attrStr=="reflect_class")
			{
				Context.CurrrentClassNode = parent;
				return ParseClass(parent);
			}
			else if (attrStr=="reflect_function")
			{
				return ParseFunction(parent);
			}
			else if (attrStr=="reflect_property")
			{
				return ParseProperty(parent);
			}
			else
			{
				return CXChildVisit_Recurse;
			}
		}
		return CXChildVisit_Recurse;
	}

	CXChildVisitResult ParseClass(CXCursor classNode)
	{
		std::string className = Util::DisplayName(classNode);
		MetaClass meta(className);
		meta.FileName = Context.FileName;
		MetaInfo::RegisterMetaClass(meta);
		return CXChildVisit_Recurse;
	}
	CXChildVisitResult ParseFunction(CXCursor functionNode)
	{
		std::string funName = Util::CursorSpelling(functionNode);
		MetaFunction meta(funName);
		meta.ClassName = Util::DisplayName(Context.CurrrentClassNode);
		auto funVisitor = [](CXCursor paramCursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
			CXCursorKind paramKind = clang_getCursorKind(paramCursor);
			if (paramKind == CXCursor_ParmDecl)
			{
				std::string paramTypeStr = Util::CursorTypeSpelling(paramCursor);
				std::string paramNameStr = Util::DisplayName(paramCursor);
				MetaFunction* m = static_cast<MetaFunction*>(client_data);
				m->Type_ParamName.emplace_back(std::make_pair(paramTypeStr, paramNameStr));
			}
			return CXChildVisit_Continue;
			};
		clang_visitChildren(functionNode, funVisitor, &meta);

		MetaInfo::RegisterMetaFunction(meta);
		return CXChildVisit_Recurse;
	}

	CXChildVisitResult ParseProperty(CXCursor propertyNode)
	{
		std::string name = Util::CursorSpelling(propertyNode);
		std::string typeNmae = Util::CursorTypeSpelling(propertyNode);
		MetaProperty meta(name);
		meta.TypeName = typeNmae;
		meta.ClassName = Util::DisplayName(Context.CurrrentClassNode);
		MetaInfo::RegisterMetaProperty(meta);
		return CXChildVisit_Recurse;
	}
}

