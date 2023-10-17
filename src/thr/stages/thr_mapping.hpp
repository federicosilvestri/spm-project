//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_MAPPING_HPP
#define SPM_PROJECT_THR_MAPPING_HPP

#include "string"
#include "vector"
#include "sstream"
#include "../../common/huffman_map.hpp"


/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_input The file to be read.
 * @return A stream of characters
 */
std::stringstream thr_mapping(HuffMap &huff_map, const std::string &file_input, unsigned int p_degree);

#endif //SPM_PROJECT_THR_MAPPING_HPP
