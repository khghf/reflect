workspace "Reflection"
    architecture"x64"
    configurations { "Debug", "Release" }
    startproject"ReflectionTest"
outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include"./CodeGenerator"
include"./Reflect"
include"./ReflectionTest"