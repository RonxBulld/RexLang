//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_ERROR_H
#define OPENELANGUAGE_ERROR_H

namespace opene {

    template <typename T>
    class ErrOr {
    private:
        // 0表示没有错误
        int error_id_ = 0;

        T *value_ = nullptr;

    public:
        bool NoError() const { return this->error_id_ == 0; }

        int GetErrorID() const { return this->error_id_; }
    };

}

#endif //OPENELANGUAGE_ERROR_H
