//
// Created by rex on 2020/7/12.
//

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    /******************************************************
     * HierarchyIdentifier
     ******************************************************/

    void HierarchyIdentifier::AppendComponent(NameComponent *component) {
        this->name_components_.push_back(component);
        setChild(component);
    }

    /******************************************************
     * NameComponent
     ******************************************************/

    NameComponent * NameComponent::Forward() const {
        if (HierarchyIdentifier *hierarchy_identifier = rtti::dyn_cast<HierarchyIdentifier>(getParent())) {
            int index = hierarchy_identifier->indexOf(this);
            if (index >= 0) {
                index--;
                return index >= 0 ? hierarchy_identifier->getNameComponents()[index] : nullptr;
            } else {
                assert(false);
                return nullptr;
            }
        } else if (ArrayIndex *array_index = rtti::dyn_cast<ArrayIndex>(getParent())) {
            return array_index->Forward();
        } else {
            assert(false);
            return nullptr;
        }
    }
    NameComponent * NameComponent::Backward() const {
        if (HierarchyIdentifier *hierarchy_identifier = rtti::dyn_cast<HierarchyIdentifier>(getParent())) {
            int index = hierarchy_identifier->indexOf(this);
            if (index >= 0) {
                index++;
                return index < hierarchy_identifier->getNameComponents().size() ? hierarchy_identifier->getNameComponents()[index] : nullptr;
            } else {
                assert(false);
                return nullptr;
            }
        } else if (ArrayIndex *array_index = rtti::dyn_cast<ArrayIndex>(getParent())) {
            return array_index->Backward();
        } else {
            assert(false);
            return nullptr;
        }
    }

}