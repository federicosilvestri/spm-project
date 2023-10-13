//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_HUFFMAN_BUILDER_HPP
#define SPM_PROJECT_HUFFMAN_BUILDER_HPP
#include "huffman_tree.hpp"
#include "unordered_map"

/**
 * @brief Build the Huffman tree
 * @param data_map the hashmap between characters and frequencies.
 * @return The HuffNode class that represents the root of tree.
 */
HuffNode* build_huffman_tree(std::unordered_map<char, unsigned int> &data_map);

/**
 * @brief Builds an hashmap that contains the pair <character, encoded_string>
 * @param tree The Huffman tree
 * @return Unordered Map (HashMap) of <char, string>
 */
std::unordered_map<char, std::string> build_huffman_map(HuffNode* tree);

#endif //SPM_PROJECT_HUFFMAN_BUILDER_HPP
