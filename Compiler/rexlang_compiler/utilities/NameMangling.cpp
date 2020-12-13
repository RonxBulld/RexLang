/*
 * 本文件实现了针对声明类型节点的名称修饰
 * Rexfield
 * 2020/12/13
 */

#include <sstream>

#include "../NodeDecl.h"
#include "../rtti.h"

namespace rexlang {
    StringRef TagDecl::getMangling() const {
        return StringPool::Create("_Z", getSelfMangling());
    }

    StringRef TagDecl::getSelfMangling() const {
        return StringPool::Create(std::to_string(getNameRef().size()), getNameRef().str());
    }

    StringRef ProgSetDecl::getSelfMangling() const {
        std::stringstream mangling_ss;
        mangling_ss << "N";
        mangling_ss << TagDecl::getSelfMangling().str();
        return StringPool::Create(mangling_ss.str());
    }

    StringRef FunctionDecl::getSelfMangling() const {
        std::stringstream mangling_ss;

        // 父级名字空间

        mangling_ss << rtti::dyn_cast<TagDecl>(getParent())->getSelfMangling().str();

        // 方法名称

        mangling_ss << TagDecl::getSelfMangling().str();

        // 形参类型表

        mangling_ss << getParameters().size();
        for (ParameterDecl *parameter_decl : getParameters()) {
            mangling_ss << parameter_decl->getType()->getSelfMangling().str();
        }

        // 结束

        mangling_ss << "E";
    }

}
