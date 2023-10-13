//
// Created by Federico Silvestri on 09/10/23.
//

#include "seq_impl.hpp"
#include "string"
#include "chrono"

#include "stages/seq_freq_map.h"
#include "../common/huffman_builder.hpp"
#include "stages/seq_encoding.hpp"
#include "../common/file_writer.hpp"

using namespace std;

void seq_impl(const string &file_input, const string &file_output, bool enable_measures) {
    // STAGE 0: Reading and computing frequencies
    auto start = chrono::high_resolution_clock::now();
    auto freq_map = seq_compute_frequencies(file_input);
    auto reading_time = chrono::high_resolution_clock::now() - start;

    // STAGE 1: Computing Huffman Tree and Huffman Map
    auto start2 = chrono::high_resolution_clock::now();
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto huff_time = chrono::high_resolution_clock::now() - start2;

    // STAGE 2: Encoding the file into memory
    auto start3 = chrono::high_resolution_clock::now();
    auto encoded_binary = seq_encode(huff_map, file_input);
    auto encoding_time = chrono::high_resolution_clock::now() - start3;

    // STAGE 3: Writing into fs
    auto start4 = chrono::high_resolution_clock::now();
    write_compressed_file(encoded_binary, file_output);
    auto writing_time = chrono::high_resolution_clock::now() - start4;


    auto total_time = chrono::high_resolution_clock::now() - start;

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        cout << "READING=" << reading_time << endl;
        cout << "HUFFBUILD=" << huff_time << endl;
        cout << "ENCODING=" << encoding_time << endl;
        cout << "WRITING=" << writing_time << endl;
        cout << "TOTAL=" << total_time << endl;
    }

}