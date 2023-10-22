//
// Created by Federico Silvestri on 09/10/23.
//

#ifndef SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP
#define SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP

#include <iostream>
#include "../../common/data_types.hpp"

/**
 * @brief Build the frequency map by reading a text file.
 * @param file_content the file to be read
 * @return the computed frequencies for each character
 */
FrequencyMap seq_compute_frequencies(const std::string& file_content);

#endif //SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP
