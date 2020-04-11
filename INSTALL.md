# 安装导引

本文档将指引你从源码构建 OpenELanguage 系统。

## 准备工作

1. 首先你需要确认已经正确的安装了 Antlr4 和 Clang/LLVM；

2. 确保你安装了 pkg-config、uuid、Python3、make 和 CMake;

3. 确保你正确安装了编译器。

## 构建第三方库

1. 进入 3rdparty 目录，执行以下指令：

> python3 build.py

## 构建 OpenELanguage

1. 进入源码根目录，依次执行以下指令：

Linux:
>
> mkdir build
>
> cd build
>
> cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ..
>
> make -j4

Windows:
>
> mkdir build
>
> cd build
>
> cmake -DLLVM_DIR=`你的LLVM安装路径`\lib\cmake\llvm -DCMAKE_PROGRAM_PATH=`你的LLVM安装路径`\bin -G "Visual Studio 15 2017 Win64" ..
>
> 在 VisualStudio 中完成构建
