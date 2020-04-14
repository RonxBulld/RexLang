//
// Created by Administrator on 2020/4/14.
//

#ifndef __REXLANG_CDECL_H__
#define __REXLANG_CDECL_H__

#include <string>
#include <vector>

struct InterfaceDeclare {
};

/*!
 * 读取指定文件的接口定义
 * @param filePath C头文件路径
 * @param args 传递给C前端的选项
 * @return 成功返回0，失败返回非0
 */
int ReadDeclFiles(std::string filePath, const std::vector<std::string> &args, struct InterfaceDeclare &interfaceDeclare);

#endif //__REXLANG_CDECL_H__
