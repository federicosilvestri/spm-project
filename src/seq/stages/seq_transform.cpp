//
// Created by federicosilvestri on 17/10/23.
//

#include "seq_transform.hpp"
#include "bitset"
#include "iostream"
using namespace std;

std::stringstream seq_transform(std::string &binary_string) {
    stringstream ss;
    for (auto i = 0; i < binary_string.size(); i+=8) {
        bitset<8> group(binary_string.substr(i, 8));
        char c = (char) (group.to_ulong() & 0xFF);
        ss << c;

    }
    return ss;
}