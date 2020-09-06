//
// Created by rex on 2020/7/12.
//

#include "NodeDecl.h"

namespace rexlang {

    /******************************************************
     * HierarchyIdentifier
     ******************************************************/

    void HierarchyIdentifier::AppendComponent(NameComponent *component) {
        if (!this->name_components_.empty()) {
            NameComponent *forward = this->name_components_.back();
            forward->SetBackward(component);
            component->SetForward(forward);
        }
        this->name_components_.push_back(component);
        setChild(component);
    }

    /******************************************************
     * NameComponent
     ******************************************************/

    void            NameComponent::SetForward   (NameComponent *component)  { forward_name_component_  = component; }
    void            NameComponent::SetBackward  (NameComponent *component)  { backward_name_component_ = component; }
    NameComponent * NameComponent::Forward      () const                    { return forward_name_component_;  }
    NameComponent * NameComponent::Backward     () const                    { return backward_name_component_; }

}