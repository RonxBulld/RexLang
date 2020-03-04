//
// Created by rex on 2020/1/22.
//

#ifndef OPENELANGUAGE_LOCATION_H
#define OPENELANGUAGE_LOCATION_H

#include <map>
#include "../common_rt/StringRef.h"

namespace opene {

    struct Location {
        StringRef filename_;
        size_t line_ = 0;
        size_t column_ = 0;
    };

    class LocationPool {
    private:
        std::map<size_t, Location> location_map_;
    public:
        size_t CreateLocation(const StringRef &filename, size_t line, size_t column);

        const StringRef &GetFilename(size_t location_id) const;

        size_t GetLineNumber(size_t location_id) const;

        size_t GetColumnNumber(size_t location_id) const;
    };

}

#endif //OPENELANGUAGE_LOCATION_H
