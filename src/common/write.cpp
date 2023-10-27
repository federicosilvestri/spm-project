//
// Created by federicosilvestri on 13/10/23.
//

#include "write.hpp"
#include "fstream"

using namespace std;

void write_compressed_file(const string& ascii_stream, const string &file_output) {
    ofstream fp(file_output, ios::out | ios::trunc);
    if (!fp.is_open()) {
        throw invalid_argument("Cannot open the file for writing the compressed file.");
    }

    // stream operator
    fp.write(&ascii_stream[0], sizeof(char) * ascii_stream.size());

    fp.close();
}
