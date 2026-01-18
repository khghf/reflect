project "ReflectionTest"
    kind"ConsoleApp"
    language"C++"
    cppdialect"C++17"
    staticruntime"off"
    targetdir("../bin/"..outputdir.."/%{prj.name}")
    objdir("../bin-int/"..outputdir.."/%{prj.name}")
    files{
        "Src/**.h",
        "Src/**.cpp",
    }
    includedirs{
        "../Reflect",
        "../Reflect/GeneratedCode",--生成的代码所在目录，路径错误则无法运行
        "../Reflect/Src"
    }
    links{
        "Reflect"
    }
    filter"configurations:Debug"
		runtime"Debug"
		symbols"on"
	filter"configurations:Release"
		runtime"Release"
		optimize"on"
    