//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "iostream"
#include "fstream"
#include "seq_mapping.hpp"

using namespace std;


void padding(string *binary) {
    auto oct_diff = 8 - (binary->size() % 8);

    if (oct_diff > 0) {
        binary->append(string(oct_diff, '0'));
    }
}

string seq_mapping(HuffMap &huff_map, const string& file_content) {
    /*
     * Maps the content of the file into a binary code.
     */
    string encoded;

    for (char c: file_content) {
        encoded += huff_map.at(c);
    }

    padding(&encoded);
    return encoded;
}