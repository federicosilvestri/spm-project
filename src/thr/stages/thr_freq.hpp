//
// Created by federicosilvestri on 09/10/23.
//

#ifndef SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
#define SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP

// #define GMR_IMP if you want to enable Google Map Reduce

#include "string"
#include "../../common/frequency.hpp"
#include "iostream"

/**
 * @brief Compute the frequencies for each character in a given input text file.
 * @param file_content the content of the file
 * @param p_degree degree of parallelism
 * @return the computed map of char and its frequency
 */
FrequencyMap thr_compute_frequencies(const std::string *content, unsigned int p_degree);

#endif //SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
