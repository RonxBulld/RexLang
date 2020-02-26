//
// Created by rex on 2020/2/17.
//

#include "LLVMRTIRBuilder.h"

namespace opene {   // 数组
    llvm::Type *ArrayRT::CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions) {
        llvm::StructType *array_struct = llvm::StructType::create(Context, "$ArrayStructTy");
        llvm::Type *dimension_count = Builder.getInt32Ty();
        llvm::Type *dimensions_ptr = Builder.getInt32Ty()->getPointerTo();
        llvm::Type *datas_ptr = elementType->getPointerTo();
        array_struct->setBody(dimension_count, dimensions_ptr, datas_ptr);
        return array_struct->getPointerTo();
    }
}

namespace opene {   // 字节集
    llvm::Type *DataSetRT::CreateDataSetType() {
        llvm::StructType *dataset_struct = llvm::StructType::create(Context, "$DataSetStructTy");
        llvm::Type *dataset_length = Builder.getInt32Ty();
        llvm::Type *data_ptr = Builder.getInt8Ty()->getPointerTo();
        dataset_struct->setBody(dataset_length, data_ptr);
        return dataset_struct->getPointerTo();
    }
}

namespace opene {   // 字符串
    llvm::Type *StringRT::CreateStringType() {
        llvm::StructType *string_struct = llvm::StructType::create(Context, "$StringStructTy");
        llvm::Type *string_length = Builder.getInt32Ty();
        llvm::Type *data_ptr = Builder.getInt8Ty()->getPointerTo();
        string_struct->setBody(string_length, data_ptr);
        return string_struct->getPointerTo();
    }
}
