//
// Created by rex on 2020/3/20.
//

#ifndef OPENELANGUAGE_CONTAINERUTIL_H
#define OPENELANGUAGE_CONTAINERUTIL_H


class ContainerUtil {
public:
    template <template <typename> typename ContainerTy, typename ElemTy, typename Pred>
    static void Foreach(ContainerTy<ElemTy> &container, const Pred & pred) {
        for (ElemTy &elem : container) {
            pred(elem);
        }
    }

    template <
            template <typename> typename DstContainerTy,
            typename DstElemTy,
            template <typename> typename SrcContainerTy,
            typename SrcElemTy,
            typename Pred
            >
    static DstContainerTy<DstElemTy> Map(SrcContainerTy<SrcElemTy> &container, const Pred & pred) {
        DstContainerTy<DstElemTy> __dest;
        for (SrcElemTy &elem : container) {
            __dest.push_back(pred(elem));
        }
        return __dest;
    }

    template <template <typename> typename ContainerTy, typename ElemTy>
    static bool InSet(const ContainerTy<ElemTy> &container, const ElemTy &findElem) {
        for (const ElemTy &elem : container) {
            if (elem == findElem) {
                return true;
            }
        }
        return false;
    }
};


#endif //OPENELANGUAGE_CONTAINERUTIL_H
