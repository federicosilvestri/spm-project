//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_MAPPING_HPP
#define SPM_PROJECT_THR_MAPPING_HPP

#include "string"
#include "vector"
#include "sstream"
#include "../../common/huffman_map.hpp"
#include "../../utils/thread_pool.hpp"


/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_content The file content
 * @param tp ThreadPool
 * @return A string of binary characters
 */
std::string thr_mapping(HuffMap &huff_map, const std::string& file_content, SuperThreadPool& tp);

#endif //SPM_PROJECT_THR_MAPPING_HPP
