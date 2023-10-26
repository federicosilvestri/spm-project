//
// Created by federicosilvestri on 09/10/23.
//

#ifndef SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
#define SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
#include "string"
#include "../../common/data_types.hpp"
#include "../../utils/thread_pool.hpp"

/**
 * @brief Compute the frequencies for each character in a given input text file.
 * @param file_content the content of the file
 * @param thread_pool the thread pool to be used
 * @return the computed map of char and its frequency
 */
FrequencyMap thr_compute_frequencies(const std::string &content, SuperThreadPool& thread_pool);

#endif //SPM_PROJECT_THR_FREQUENCY_MAPPER_HPP
