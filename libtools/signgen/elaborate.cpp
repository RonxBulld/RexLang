//
// Created by Administrator on 2020/4/18.
//

#include "elaborate.h"
#include "../CDecl/cdecl.h"

int ElaborateVariArgs(struct InterfaceDeclare &interfaceDeclare) {
    std::vector<struct ParameterDesc> &parameterList = interfaceDeclare.parameters;
    size_t parm_count = parameterList.size();
    if (parm_count < 2) {
        return 0;
    }
    TypeDesc &arg1ty = parameterList[parm_count - 2].type_desc;
    TypeDesc &arg2ty = parameterList[parm_count - 1].type_desc;
    bool cond1 = (arg1ty.base_typename == "i32" && !arg1ty.is_nullable && !arg1ty.is_reference && !arg1ty.is_array);
    bool cond2 = (arg2ty.base_typename == "SimpleRTArguInfo" && (arg2ty.is_reference || arg2ty.is_array ) && !arg2ty.is_nullable);
    if (cond1 && cond2) {
        parameterList.pop_back();
        parameterList.pop_back();
        struct ParameterDesc __args_desc;
        __args_desc.type_desc.base_typename = "*";
        __args_desc.type_desc.is_array = false;
        __args_desc.type_desc.is_reference = false;
        __args_desc.type_desc.is_nullable = false;
        __args_desc.parameter_comments.comments.emplace_back("长度可变参数列表");
        __args_desc.parameter_name = "...";
        __args_desc.index = parameterList.size();
        parameterList.emplace_back(__args_desc);
        interfaceDeclare.interface_api_name.append("#");
    }
    return 0;
}

int Elaborate::ElaborateInterface(struct InterfaceDeclare &interfaceDeclare) {
    auto &parameter_list = interfaceDeclare.parameters;
    if (int v = ElaborateVariArgs(interfaceDeclare)) {
        return v;
    }
    return 0;
}
