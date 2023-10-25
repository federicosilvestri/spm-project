//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_HUFFMAN_BUILDER_HPP
#define SPM_PROJECT_HUFFMAN_BUILDER_HPP
#include "huffman_tree.hpp"
#include "unordered_map"

#include "../common/data_types.hpp"

/**
 * @brief Build the Huffman tree
 * @param f_map the hashmap between characters and frequencies.
 * @return The HuffNode class that represents the root of tree.
 */
HuffNode* build_huffman_tree(FrequencyMap &f_map);

/**
 * @brief Builds an hashmap that contains the pair <character, encoded_string>
 * @param tree The Huffman tree
 * @return Unordered Map (HashMap) of <char, string>
 */
HuffMap build_huffman_map(HuffNode* tree);


/**
 * @brief Compute the size of compressed file, using as information the frequency and the size of the code.
 * @param huff_map HuffMap to be used for computation
 * @return number of bits of compressed file
 */
unsigned long compute_huffman_size(HuffMap &huff_map);

#endif //SPM_PROJECT_HUFFMAN_BUILDER_HPP
