#include "CodeParser.h"
#include<iostream>
#include"../Util.h"
#include"../Meta/MetaInfo.h"
using namespace std;

namespace reflect
{
	struct ParseContext
	{
		CXCursor CurrrentClassNode;
		MetaFile* CurMetaFile = nullptr;
		MetaClass* CurMetaClass = nullptr;
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
		std::vector<std::string>filePaths = Util::GetAllFilePath(m_ScanDirectory, true);
		for (const auto& path : filePaths)
		{
			if (Util::GetFileSuffix(path) != "h")continue;
			Parse(path);
		}
	}


	void CodeParser::Parse(const std::string_view& filePath)
	{

		CXTranslationUnit unit;
		const char* arguments[] = {
		"-x", "c++-header",
		"-std=c++17",
		"-DENABLE_PARSER",
		"-include", "Src/ReflectMarco.h",//指定文件目录以便libclang解析器能找到反射宏定义并展开，若不指定则在反射宏.h和要扫描的文件不在同一目录时解析器不会对宏展开
		};
		//std::cout << Util::IsFileExist("D:/Reflection/CodeGenerator/Src/ReflectMarco.h") << std::endl; return;
		int argCount = sizeof(arguments) / sizeof(arguments[0]);
		unsigned options = CXTranslationUnit_DetailedPreprocessingRecord | CXTranslationUnit_SkipFunctionBodies;
		CXErrorCode errorCode = clang_parseTranslationUnit2(m_Index, filePath.data(), arguments, argCount, nullptr, 0, options, &unit);
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
		MetaFile meta(filePath.data());
		meta.LastIncludeLine = 2;//Util::GetIncludeNumInFile(Util::ModifySuffix(meta.Path,"h"));
		Context.CurMetaFile=MetaInfo::RegisterMetaFile(meta);
		Context.CurMetaClass = nullptr;
		CXCursor root = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(root, CursorVisitor, nullptr);
		clang_disposeTranslationUnit(unit);
	}

	

	std::vector<std::string> CodeParser::GetClassNameSpace(CXCursor classNode)
	{
		std::vector<std::string> res;
		CXCursor CurCursor = classNode;
		while (true) {
			// 获取当前节点的语义父节点
			CXCursor parentCursor = clang_getCursorSemanticParent(CurCursor);
			if (clang_getCursorKind(parentCursor) == CXCursor_TranslationUnit) {
				break;
			}
			// 判断父节点是否为命名空间
			if (clang_getCursorKind(parentCursor) == CXCursor_Namespace) {
				// 获取命名空间名称并存入向量
				res.push_back(Util::CursorSpelling(parentCursor));
			}
			// 向上移动到父节点，继续回溯
			CurCursor = parentCursor;
		}
		return res;
	}

	CXChildVisitResult CursorVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
	{
		//跳过对主文件和ReflectMarco.h以外的文件的解析
		if (!Util::IsTargetHeaderCursor(cursor, "ReflectMarco.h")&& !Util::IsTargetHeaderCursor(cursor,Util::GetFileName(Context.CurMetaFile->Path,true)))
		{
			return CXChildVisit_Continue;
		}
		std::cout << Util::DisplayName(cursor) << std::endl;
		CXCursorKind c_kind = clang_getCursorKind(cursor);
		if (c_kind == CXCursor_InclusionDirective)
		{
		}
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
		
		//记录REFLECT_BODY()宏的位置
		if (c_kind == CXCursor_MacroExpansion)
		{
			if (Util::DisplayName(cursor) == "REFLECT_BODY")
			{
				uint32_t line = 0, col = 0;
				Util::GetCursorLocation(cursor, &line, &col);

				if (Context.CurMetaFile)
				{
					Context.CurMetaFile->ReflectBodyMarcoLine.push_back(line);
				}
			}
		}
		//获取父类名字
		if (c_kind == CXCursor_CXXBaseSpecifier)
		{
			if (Context.CurMetaClass)
			{
					
				CX_CXXAccessSpecifier AccessSpecifier=	clang_getCXXAccessSpecifier(cursor);
				std::string accessName;
				switch (AccessSpecifier)
				{
				case CX_CXXInvalidAccessSpecifier:
					accessName = "None";
					break;
				case CX_CXXPublic:
					accessName = "public";
					break;
				case CX_CXXProtected:
					accessName = "protected";
					break;
				case CX_CXXPrivate:
					accessName = "private";
					break;
				}
				std::string superClassName = Util::GetStrBehindLastChar(Util::DisplayName(cursor), ":");
				Context.CurMetaClass->SuperClassesName.emplace_back(accessName, superClassName);
			}
		}
		return CXChildVisit_Recurse;
	}

	CXChildVisitResult ParseClass(CXCursor classNode)
	{
		std::string className = Util::DisplayName(classNode);
		MetaClass meta(className);
		meta.FilePath = Context.CurMetaFile->Path;
		meta.NameSpaces=CodeParser::GetClassNameSpace(classNode);
		meta.ReflectBodyLine = std::to_string(Context.CurMetaFile->ReflectBodyMarcoLine[Context.CurMetaFile->CurClassMarcoIndex++]);
		Context.CurMetaClass=MetaInfo::RegisterMetaClass(meta);
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

