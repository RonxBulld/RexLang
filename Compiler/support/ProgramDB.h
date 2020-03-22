//
// Created by rex on 2020/3/22.
//

#ifndef OPENELANGUAGE_PROGRAMDB_H
#define OPENELANGUAGE_PROGRAMDB_H

#include <string>
#include <vector>

namespace opene {

    class ArgumentParser;

    class ProgramDB {
    private:
        std::vector<std::string> execute_path_;
        std::vector<std::string> include_path_;
        std::vector<std::string> library_path_;

    public:
        bool ApplyArgument(const ArgumentParser &argumentParser);

        void SetProgramPath(const char *programPath);
        const std::vector<std::string> &GetExecutePath() const;
        const std::vector<std::string> &GetIncludePath() const;
        const std::vector<std::string> &GetLibraryPath() const;
    };

    extern ProgramDB program_db;
}

#endif //OPENELANGUAGE_PROGRAMDB_H
