//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "NodeDecl.h"
#include "Str2Attr.h"

namespace opene {
    bool SematicAnalysis::Run(TranslateUnit * translateUnitPtr) {

        if (translateUnitPtr->edition_ != 2) {
            translateUnitPtr->ast_context_->GetDiagnostic()->EditionWrong(translateUnitPtr->edition_);
            return false;
        }
        this->translate_unit_ = translateUnitPtr;
        // 1. 创建内置数据类型并写入索引表
        // 2. 针对所有的数据结构定义和类模块定义
        // 2.1. 抽取至全局
        for (SourceFilePtr sfptr : translateUnitPtr->source_file_) {
            if (DataStructureFile *data_structure_file_ptr = sfptr->as<DataStructureFile>()) {
            }
        }
        // 2.2. 明确每一个变量或成员的类型指针
        // 3. 针对所有的程序集和DLL声明列表将定义抽取至全局
        // 4. 针对每一个程序集中的每一个函数开始遍历
        // 4.1. 明确每一个参数和局部变量的类型指针
        // 4.2. 明确每一条语句构造是否合法
        // 4.3. 明确每一个表达式运算是否合法
        // 4.4. 明确每一个名称引用的定义

    }

}
