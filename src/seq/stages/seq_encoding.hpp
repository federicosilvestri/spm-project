//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_SEQ_ENCODING_HPP
#define SPM_PROJECT_SEQ_ENCODING_HPP
#include "string"
#include "unordered_map"

// to be commented, but it's a function
// that encode a string into a binary string
std::string seq_encode(std::unordered_map<char, std::string> huff_map, const std::string &file_input);

#endif //SPM_PROJECT_SEQ_ENCODING_HPP
