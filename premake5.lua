-- premake5.lua
workspace Reflect
    -- 工作区配置：对应 VS 解决方案
    configurations { Debug, Release }  -- 配置类型：DebugRelease
    platforms { x64 }  -- 目标平台：x64（匹配你的 Debug x64 配置）
    location .build  -- 生成的 VS 项目文件存放目录

    -- 全局编译器配置：切换到 ClangCL 工具集（核心配置）
    toolset clangcl  -- 关键：指定使用 ClangCL 编译器（VS 原生支持的 Clang 工具集）

    -- 全局 CC++ 配置
    filter configurations
        system windows  -- 目标系统：Windows
        cppdialect C++17  -- 关键：启用 C++17 标准（支持 annotate 注解的前提）
        characterset Unicode  -- 字符集：Unicode（VS 项目默认配置）

    -- Debug 配置
    filter configurationsDebug
        defines { DEBUG, ENABLE_PARSER }  -- 定义 DEBUG 和 ENABLE_PARSER 宏
        symbols On  -- 生成调试信息
        optimize Off  -- 关闭优化

    -- Release 配置
    filter configurationsRelease
        defines { NDEBUG, ENABLE_PARSER }  -- 定义 NDEBUG 和 ENABLE_PARSER 宏
        optimize Speed  -- 优化为运行速度
        symbols Off  -- 关闭调试信息

    -- 重置过滤器
    filter {}

project Reflect
    -- 项目配置：对应 VS 项目
    kind ConsoleApp  -- 项目类型：控制台应用（可根据你的需求改为 StaticLibDLL）
    language C++  -- 开发语言：C++

    -- 源文件列表（替换为你的实际源文件路径）
    files {
        ..h,
        ..cpp
    }

    -- 头文件目录（若有额外头文件目录，添加此处）
    includedirs {
        .,
        .LLVMinclude  -- 可添加 libclang 头文件目录（若需要）
    }

    -- 链接器配置（若需要链接 libclang，添加此处）
    filter configurations
        libdirs { .LLVMlibx64 }  -- libclang 库文件目录
        links { libclang.lib }  -- 链接 libclang 导入库

    -- 额外编译选项：启用 Clang 扩展（支持 __attribute__((annotate)) 注解）
    filter toolsetclangcl
        buildoptions {
            -Wall  -- 启用所有警告（可选，可添加其他 Clang 编译选项）
        }