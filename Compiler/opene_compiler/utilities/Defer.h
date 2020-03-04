//
// Created by rex on 2020/3/1.
//

#ifndef OPENELANGUAGE_DEFER_H
#define OPENELANGUAGE_DEFER_H

namespace opene {
    template <typename Pred>
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
}

#endif //OPENELANGUAGE_DEFER_H
