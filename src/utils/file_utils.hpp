//
// Created by Federico Silvestri on 09/10/23.
//

#ifndef SPM_PROJECT_FILE_UTILS_HPP
#define SPM_PROJECT_FILE_UTILS_HPP

#include "string"
#include <sys/stat.h>
#include <string>
#include "fstream"


inline bool file_exists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}

inline long file_size(const std::string &name) {
    // getting file size
    std::ifstream fp(name, std::ios::binary);
    fp.seekg(0, std::ios::end);
    // computing chunk size
    auto f_size = fp.tellg();
    fp.close();
    return f_size;
}

#endif //SPM_PROJECT_FILE_UTILS_HPP
