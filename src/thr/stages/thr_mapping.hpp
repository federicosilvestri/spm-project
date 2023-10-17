//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_MAPPING_HPP
#define SPM_PROJECT_THR_MAPPING_HPP

#include "string"
#include "vector"
#include "../../common/huffman_map.hpp"

/**
 * @brief A vector of string, ordered, one for each chunk of data.
 */
struct EncodedChunks {
    std::vector<std::string> chunks;

    /**
     * @brief Get the length of all strings (the sum of their size).
     * @return unsigned long
     */
    unsigned long length() {
        unsigned long l = 0;
        for (auto &v: chunks) {
            l += v.size();
        }

        return l;
    }

    void pad() {
        unsigned long s_len = length();
        if (s_len != 0) {
            // add to last vector of string zeros
            auto size = 8 - (s_len % 8);
            chunks[chunks.size() - 1] += std::string(size, '0');
        }
    }
};

/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_input The file to be read.
 * @return A vector that contains all string encoded.
 */
EncodedChunks thr_mapping(HuffMap &huff_map, const std::string &file_input, unsigned int p_degree);

#endif //SPM_PROJECT_THR_MAPPING_HPP
