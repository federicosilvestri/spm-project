//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_FF_FREQ_HPP
#define SPM_PROJECT_FF_FREQ_HPP
#include "../../common/data_types.hpp"

/**
 * @brief Compute the frequencies for each character in a given input text file.
 * @param file_content the content of the file
 * @param p_degree degree of parallelism
 * @return the computed map of char and its frequency
 */
FrequencyMap ff_compute_frequencies(const std::string &content, unsigned int p_degree);

#endif //SPM_PROJECT_FF_FREQ_HPP
