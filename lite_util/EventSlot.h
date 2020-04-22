//
// Created by rex on 2020/4/22.
//

#ifndef REXLANG_EVENTSLOT_H
#define REXLANG_EVENTSLOT_H

#include <vector>
#include <functional>

namespace rexlang {

    class Event {
    public:
        virtual ~Event() = default;
    };

    class EventSlot {
    private:
        std::vector<std::function<int(const Event *)>> slot_;

    public:
        EventSlot() = default;
        virtual ~EventSlot() = default;

    public:
        template <typename Callable>
        int Subscribe(const Callable & callable) {
            this->slot_.emplace_back(callable);
        }

        int Publish(const Event *event) {
            for (const std::function<int(const Event *)> &handler : this->slot_) {
                handler(event);
            }
            return 0;
        }
    };

}

#endif //REXLANG_EVENTSLOT_H
