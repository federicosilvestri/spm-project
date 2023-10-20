//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_HUFFMAN_MAP_HPP
#define SPM_PROJECT_HUFFMAN_MAP_HPP
#include "huffman_tree.hpp"
#include "unordered_map"

#include "../common/data_types.hpp"

/**
 * @brief Here I define for simplicity a new type for HuffMap.
 */
typedef std::unordered_map<char, std::string> HuffMap;

/**
 * @brief Build the Huffman tree
 * @param data_map the hashmap between characters and frequencies.
 * @return The HuffNode class that represents the root of tree.
 */
HuffNode* build_huffman_tree(FrequencyMap &data_map);

/**
 * @brief Builds an hashmap that contains the pair <character, encoded_string>
 * @param tree The Huffman tree
 * @return Unordered Map (HashMap) of <char, string>
 */
HuffMap build_huffman_map(HuffNode* tree);

#endif //SPM_PROJECT_HUFFMAN_MAP_HPP
