//
// Created by Federico Silvestri on 09/10/23.
//

#include "seq_impl.hpp"
#include "stages/seq_freq_map.h"
#include "string"
#include "chrono"

#include "../common/huffman_builder.hpp"

using namespace std;

void seq_impl(const string &file_input, const string &file_output, bool enable_measures) {
    auto start = chrono::high_resolution_clock::now();
    auto freq_map = seq_compute_frequencies(file_input);
    auto reading_time = chrono::high_resolution_clock::now() - start;

    auto start2 = chrono::high_resolution_clock::now();
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto huff_time = chrono::high_resolution_clock::now() - start2;

    // other steps go here...

    auto total_time = chrono::high_resolution_clock::now() - start;

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        cout << "READING=" << reading_time << endl;
        cout << "HUFFBUILD=" << huff_time << endl;
        cout << "TOTAL=" << total_time << endl;
    }


}