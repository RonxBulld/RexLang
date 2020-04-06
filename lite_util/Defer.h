//
// Created by rex on 2020/3/1.
//

#ifndef LITE_UTIL_DEFER_H
#define LITE_UTIL_DEFER_H

template<typename Pred>
class defer {
private:
    Pred &pred_;

public:
    defer(Pred &&pred) : pred_(pred) {
    }

    ~defer() {
        pred_();
    }
};

#endif //LITE_UTIL_DEFER_H
