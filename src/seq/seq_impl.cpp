//
// Created by Federico Silvestri on 09/10/23.
//

#include "seq_impl.hpp"
#include "string"
#include "../utils/my_timer.hpp"

#include "stages/seq_freq_map.h"
#include "../common/huffman_map.hpp"
#include "stages/seq_encoding.hpp"
#include "../common/file_writer.hpp"

using namespace std;

void seq_impl(const string &file_input, const string &file_output, bool enable_measures) {
    MyTimer timer;

    // STAGE 0: Reading and computing frequencies
    timer.start("READING");
    auto freq_map = seq_compute_frequencies(file_input);
    timer.stop();

    // STAGE 1: Computing Huffman Tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

    // STAGE 2: Encoding the file into memory
    timer.start("ENCODING");
    auto encoded_binary = seq_encode(huff_map, file_input);
    timer.stop();

    // STAGE 3: Writing into fs
    timer.start("WRITING");
    write_compressed_file(encoded_binary, file_output);
    timer.stop();


    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }

}