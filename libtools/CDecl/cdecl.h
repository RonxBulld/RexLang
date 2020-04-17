//
// Created by Administrator on 2020/4/14.
//

#ifndef __REXLANG_CDECL_H__
#define __REXLANG_CDECL_H__

#include <string>
#include <vector>
#include <sstream>
#include "../../lite_util/StringUtil.h"

struct CommentList {
    std::vector<std::string> comments;

    int printToString(std::stringstream &outs, const std::string& indentStr) const {
        auto quote_warp = [](const std::string &comment) -> std::string { return "\"" + comment + "\""; };
        outs << indentStr << "Comments: [" << std::endl;
        for (const std::string &comment : comments) {
            outs << indentStr << "  " << quote_warp(comment) << std::endl;
        }
        outs << indentStr << "]" << std::endl;
        return 0;
    }
};

struct TypeDesc {
    std::string base_typename;
    bool is_array = false;
    std::vector<unsigned> dimensions;
    bool is_reference = false;
    bool is_nullable = false;

    int printToString(std::ostream &outs, const std::string& indentStr) const {
        outs << (!base_typename.empty() ? base_typename : "<!unknow>" );
        if (is_array) {
            outs << StringUtil::Join(dimensions, "", [](unsigned dim)->std::string{ return "[" + std::to_string(dim) + "]"; });
        }
        outs << ", " << (is_reference ? "pass ref" : "pass value");
        outs << ", " << (is_nullable ? "default" : "no default");
        outs << std::endl;
        return 0;
    }
};

struct ParameterDesc {
    unsigned int index = -1;
    TypeDesc type_desc;
    std::string parameter_name;
    struct CommentList parameter_comments;

    int printToString(std::stringstream &outs, const std::string& indentStr) const {
        outs << indentStr << "[" << index << "] " << parameter_name << " : "; type_desc.printToString(outs, indentStr + "  ");
        parameter_comments.printToString(outs, indentStr + "  ");
        return 0;
    }
};

struct InterfaceDeclare {
    TypeDesc return_type;
    std::string return_description;
    std::string interface_api_name;
    struct CommentList interface_breif;
    std::vector<struct ParameterDesc> parameters;
    bool is_variadic = false;

    int printToString(std::stringstream &outs, const std::string &indentStr) const {
        outs << indentStr << "InterfaceAPIName: " << interface_api_name << std::endl;
        outs << indentStr << "ReturnType:"; return_type.printToString(outs, indentStr + "  ");
        outs << indentStr << "ReturnDescription: " << return_description << std::endl;
        outs << indentStr << "InterfaceBreif:" << std::endl; interface_breif.printToString(outs, indentStr + "  ");
        outs << indentStr << "isVariadic: " << is_variadic << std::endl;
        outs << indentStr << "Parameters:" << std::endl;
        for (const struct ParameterDesc &parm_desc : parameters) {
            parm_desc.printToString(outs, indentStr + "  ");
        }
        outs << std::endl;
        return 0;
    }
};

/*!
 * 读取指定文件的接口定义
 * @param filePath C头文件路径
 * @param args 传递给C前端的选项
 * @return 成功返回0，失败返回非0
 */
int ReadDeclFiles(std::string filePath, const std::vector<std::string> &args, struct InterfaceDeclare &interfaceDeclare);

#endif //__REXLANG_CDECL_H__
