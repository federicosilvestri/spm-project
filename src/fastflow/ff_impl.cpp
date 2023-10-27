//
// Created by federicosilvestri on 18/10/23.
//

#include "ff_impl.hpp"
#include "string"
#include "../utils/my_timer.hpp"
#include "../seq/stages/seq_read.hpp"
#include "stages/ff_freq.hpp"
#include "../common/huffman_builder.hpp"
#include "stages/ff_mapping.hpp"
#include "../common/write.hpp"

using namespace std;

void ff_impl(const string &file_input, const string &file_output, int p_degree, bool enable_measures) {
    MyTimer timer;

    // STAGE 0: Reading and computing frequencies
    timer.start("READ");
    auto file_content = seq_read_file(file_input);
    timer.stop();

    // STAGE 0: Reading and computing frequencies
    timer.start("FREQCALC");
    auto f_map = ff_compute_frequencies(file_content, p_degree);
    timer.stop();

    // STAGE 1: Computing Huffman Tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(f_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

    timer.start("MAP");
    auto output_buffer = ff_mapping(huff_map, file_content, p_degree);
    timer.stop();


    // STAGE 3: Writing into fs
    timer.start("WRITE");
    write_compressed_file(output_buffer, file_output);
    timer.stop();


    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }

}