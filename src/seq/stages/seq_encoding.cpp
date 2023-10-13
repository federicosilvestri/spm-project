//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "iostream"
#include "fstream"
#include "seq_encoding.hpp"

using namespace std;


void padding(string *binary) {
    auto oct_diff = 8 - (binary->size() % 8);

    if (oct_diff > 0) {
        binary->append(string(oct_diff, '0'));
    }
}

string seq_encode(unordered_map<char, string> huff_map, const string &file_input) {
    string encoded;
    ifstream file_stream;
    file_stream.open(file_input, ios::in);

    if (file_stream.is_open()) {
        char c;
        while (file_stream.get(c)) {
            if (!huff_map.contains(c)) {
                throw invalid_argument("The Huffman map does not contain this character");
            }
            encoded.append(huff_map.at(c));
            file_stream.close();
        }
    } else {
        cerr << "Cannot read file!" << endl;
        exit(1);
    }

    padding(&encoded);
    return encoded;
}