//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_SEQ_MAPPING_HPP
#define SPM_PROJECT_SEQ_MAPPING_HPP
#include "string"
#include "../../common/huffman_map.hpp"

/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_input The file to be read.
 * @return The binary string.
 */
std::string seq_mapping(HuffMap &huff_map, const std::string &file_input);

#endif //SPM_PROJECT_SEQ_MAPPING_HPP
