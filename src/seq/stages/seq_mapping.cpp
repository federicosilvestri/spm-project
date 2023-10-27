//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "iostream"
#include "fstream"
#include "seq_mapping.hpp"

using namespace std;

string seq_mapping(HuffMap &huff_map, const string &file_content) {
    /*
     * Maps the content of the file into a binary code.
     */
    string mapped;

    for (char c: file_content) {
        mapped += huff_map.at(c);
    }

    // padding
    auto oct_diff = (8 - mapped.size() % 8);
    if (oct_diff > 0) {
        mapped += string(oct_diff, '0');
    }

    return mapped;
}