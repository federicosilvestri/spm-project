//
// Created by Federico Silvestri on 09/10/23.
//

#ifndef SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP
#define SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP
#include <unordered_map>
#include <iostream>

std::unordered_map<char, unsigned int> seq_compute_frequencies(const std::string& file_input);

#endif //SPM_PROJECT_SEQ_FREQUENCY_MAPPER_HPP
