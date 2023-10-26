//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_SEQ_MAPPING_HPP
#define SPM_PROJECT_SEQ_MAPPING_HPP
#include "string"
#include "../../common/huffman_builder.hpp"

/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_content The content of the file
 * @return The binary string.
 */
OutputBuffer seq_mapping(HuffMap &huff_map, const std::string& file_content);

#endif //SPM_PROJECT_SEQ_MAPPING_HPP
