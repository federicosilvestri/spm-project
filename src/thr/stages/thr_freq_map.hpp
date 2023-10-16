//
// Created by federicosilvestri on 09/10/23.
//

#ifndef SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
#define SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP

// #define GMR_IMP if you want to enable Google Map Reduce

#include "string"
#include "unordered_map"
#include "iostream"

std::unordered_map<char, unsigned int> thr_compute_frequencies(const std::string &file_input, unsigned int p_degree);

inline void debug_map(std::unordered_map<char, unsigned int> m) {
    for (auto &r : m) {
        std::cout << "CHAR=" << r.first << " FREQ=" << r.second << std::endl;
    }
}

#endif //SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
