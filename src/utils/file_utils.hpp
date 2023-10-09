//
// Created by Federico Silvestri on 09/10/23.
//

#ifndef SPM_PROJECT_FILE_UTILS_HPP
#define SPM_PROJECT_FILE_UTILS_HPP

#include "string"
#include <sys/stat.h>
#include <string>


inline bool file_exists (const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}

#endif //SPM_PROJECT_FILE_UTILS_HPP
