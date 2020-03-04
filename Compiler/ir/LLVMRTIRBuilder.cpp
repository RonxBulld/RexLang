//
// Created by rex on 2020/2/17.
//

#include "LLVMRTIRBuilder.h"

namespace opene {   // 数组
    llvm::Type *ArrayRT::CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions) {
        DArrayType *d_array_type = new DArrayType(Context);
        d_array_type->SetElementType(elementType);
        d_array_type->SetDimensions(dimensions);
        return d_array_type;
    }
}

namespace opene {   // 字节集
    llvm::Type *DataSetRT::CreateDataSetType() {
    }
}

namespace opene {   // 字符串
    llvm::Type *StringRT::CreateStringType() {
    }
}
