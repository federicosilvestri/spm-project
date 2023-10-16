//
// Created by federicosilvestri on 13/10/23.
//

#include "file_writer.hpp"
#include "fstream"
#include "iostream"
#include "sstream"
#include "bitset"

using namespace std;

void write_compressed_file(string &binary, const string &file_output) {
    ofstream fp(file_output, ios::out);
    stringstream stream(binary);

    if (!fp.is_open()) {
        throw invalid_argument("Cannot open the file for writing the compressed file.");
    }

    while (stream.good()) {
        bitset<8> ascii_bits;
        stream >> ascii_bits;
        char c = char(ascii_bits.to_ulong());
        fp.write(&c, 1);
    }

    fp.close();
}
