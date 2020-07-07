//
// Created by rex on 2020/3/20.
//

#ifndef REXLANG_CONTAINERUTIL_H
#define REXLANG_CONTAINERUTIL_H


class ContainerUtil {
public:
    template <template <typename> typename ContainerTy, typename ElemTy, typename Pred>
    static void Foreach(ContainerTy<ElemTy> &container, const Pred & pred) {
        for (ElemTy &elem : container) {
            pred(elem);
        }
    }

    template <typename DstContainerTy, typename SrcContainerTy, typename Pred>
    static DstContainerTy Map(SrcContainerTy &container, const Pred & pred) {
        DstContainerTy __dest;
        for (auto &elem : container) {
            __dest.push_back(pred(elem));
        }
        return __dest;
    }

    template <typename ContainerTy, typename ElemTy>
    static bool InSet(const ContainerTy &container, const ElemTy &findElem) {
        for (const ElemTy &elem : container) {
            if (elem == findElem) {
                return true;
            }
        }
        return false;
    }
};


#endif //REXLANG_CONTAINERUTIL_H
