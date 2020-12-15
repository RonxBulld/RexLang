/*
 * 本文件实现了针对声明类型节点的名称修饰
 * 暂时不支持指定以何种标准mangling
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
        return StringPool::Create(getNameRef().size(), getNameRef());
    }

    StringRef ParameterDecl::getSelfMangling() const {
        return StringPool::Create(
                rtti::dyn_cast<TagDecl>(getParent())->getSelfMangling(),
                TagDecl::getSelfMangling()
                );
    }

    /*
     * ProgSetDecl
     * 本身并不组成重命名部分，因为它可能会扰乱模块函数导出和互调用
     * 只有文件变量会使用到它
     */

    StringRef ProgSetDecl::getSelfMangling() const {
        return StringPool::Create("");
    }

    /*
     * FileVariableDecl
     * 将程序集名视作命名空间进行组合
     */

    StringRef FileVariableDecl::getSelfMangling() const {
        return StringPool::Create(
                "N",
                rtti::dyn_cast<ProgSetDecl>(getParent())->TagDecl::getSelfMangling(),
                TagDecl::getSelfMangling()
                );
    }

    /*
     * GlobalVariableDecl
     * 普通的变量，直接使用其名称即可
     */

    StringRef GlobalVariableDecl::getSelfMangling() const {
        return getNameRef();
    }
    StringRef GlobalVariableDecl::getMangling() const {
        return getNameRef();
    }

    /*
     * MemberVariableDecl
     * 如同局部变量一般，成员变量并不会生成具体的符号
     * 除非是静态成员变量，但是目前尚不支持
     */

    StringRef MemberVariableDecl::getSelfMangling() const {
        assert(false);
        return StringPool::Create("");
    }

    /*
     * FunctionDecl
     * 完整层次名称+参数类型表+E
     */

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

        return StringPool::Create(mangling_ss.str());
    }

    /*
     * APICommandDecl
     * 需要按照C/cdecl命名
     */

    StringRef APICommandDecl::getSelfMangling() const {
        return getNameRef();
    }
    StringRef APICommandDecl::getMangling() const {
        return getNameRef();
    }

    /*
     * LocalVariableDecl
     * 根据是否为静态变量采取不同的策略
     */

    StringRef LocalVariableDecl::getSelfMangling() const {
        StringRef mangling = TagDecl::getSelfMangling();
        if (isStatic()) {
            mangling = StringPool::Create(rtti::dyn_cast<TagDecl>(getParent())->getSelfMangling(), mangling);
        }
        return mangling;
    }

    /*
     * ReferenceType
     * 在实际类型字符前面添加大写‘R’
     */

    StringRef ReferenceType::getSelfMangling() const {
        return StringPool::Create("R", getPointee()->getSelfMangling());
    }

}
