//
// Created by federicosilvestri on 13/10/23.
//

#include "write.hpp"
#include "fstream"
#include "iterator"

using namespace std;

void write_compressed_file(OutputBuffer &out_buff, const string &file_output) {
    ofstream fp(file_output, ios_base::binary);

    if (!fp.is_open()) {
        throw invalid_argument("Cannot open the file for writing the compressed file.");
    }

    // Write the size of metadata (to allow decompression) using uint_16
    u_int16_t metadata_size = out_buff.chunk_info.size();
    fp.write((const char *) &metadata_size, sizeof(u_int16_t));

    // Write metadata info
    fp.write((const char *) &out_buff.chunk_info[0], sizeof(u_int64_t) * out_buff.chunk_info.size());


    // Write the payload
    for (auto &inter_buff: out_buff.buffer) {
        copy(inter_buff.cbegin(), inter_buff.cend(), ostreambuf_iterator<char>(fp));
    }

    fp.close(); // forcing the flush
}
