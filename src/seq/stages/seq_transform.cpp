//
// Created by federicosilvestri on 17/10/23.
//

#include "seq_transform.hpp"
#include "bitset"
#include "iostream"

using namespace std;

std::string seq_transform(const std::string &binary_string) {
    string transformed(binary_string.size() / 8, '\0');

    for (auto i = 0, j = 0; i < binary_string.size(); i += 8, j++) {
        bitset<8> group(binary_string.substr(i, 8));
        transformed[j] = (char) (group.to_ulong() & 0xFF);
    }

    return transformed;
}