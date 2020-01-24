//
// Created by rex on 2020/1/22.
//

#include "Location.h"

namespace opene {
    size_t LocationPool::CreateLocation(const StringRef &filename, size_t line, size_t column) {
        Location location{filename, line, column};
        size_t id = this->location_map_.size() + 1;
        this->location_map_[id] = location;
        return id;
    }

    static StringRef __kEmptyFilename;
    const StringRef &LocationPool::GetFilename(size_t location_id) const {
        auto found = this->location_map_.find(location_id);
        if (found != this->location_map_.end()) {
            return found->second.filename_;
        } else {
            return __kEmptyFilename;
        }
    }

    size_t LocationPool::GetLineNumber(size_t location_id) const {
        auto found = this->location_map_.find(location_id);
        if (found != this->location_map_.end()) {
            return found->second.line_;
        } else {
            return 0;
        }
    }

    size_t LocationPool::GetColumnNumber(size_t location_id) const {
        auto found = this->location_map_.find(location_id);
        if (found != this->location_map_.end()) {
            return found->second.column_;
        } else {
            return 0;
        }
    }
}