//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_HUFFMAN_MAP_HPP
#define SPM_PROJECT_HUFFMAN_MAP_HPP
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

#endif //SPM_PROJECT_HUFFMAN_MAP_HPP
