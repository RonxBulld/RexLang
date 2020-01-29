//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_ERROR_H
#define OPENELANGUAGE_ERROR_H

#include <cassert>

namespace opene {

    template <typename T>
    class ErrOr {
    private:
        // 0表示没有错误
        int error_id_ = 0;

        T value_;

    private:
        ErrOr() = default;

    public:
        bool NoError() const { return this->error_id_ == 0; }

        bool HadError() const { return this->error_id_ != 0; }

        int GetErrorID() const { return this->error_id_; }

        const T & Value() const { return this->value_; }

        ErrOr(const T &value) : value_(value) { }

        static ErrOr<T> CreateError(int error_id) {
            assert(false);
            ErrOr<T> e;
            e.error_id_ = error_id;
            return e;
        }
    };

    template <typename T>
    ErrOr<T> MakeNoErrVal(const T &value) {
        return ErrOr<T>(value);
    }

    template <typename T>
    ErrOr<T> CreateError(int error_id) {
        return ErrOr<T>::CreateError(error_id);
    }

}

#endif //OPENELANGUAGE_ERROR_H
