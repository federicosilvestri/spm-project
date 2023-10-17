//
// Created by federicosilvestri on 13/10/23.
//

#include "file_writer.hpp"
#include "fstream"

using namespace std;

void write_compressed_file(stringstream& stream, const string &file_output) {
    ofstream fp(file_output, ios::out | ios::trunc);
    if (!fp.is_open()) {
        throw invalid_argument("Cannot open the file for writing the compressed file.");
    }

    // stream operator
    fp << stream.rdbuf();

    fp.close();
}
