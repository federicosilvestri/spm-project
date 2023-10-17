//
// Created by federicosilvestri on 09/10/23.
//

#include "thr_impl.hpp"
#include "stages/thr_freq_map.hpp"
#include "../common/huffman_map.hpp"
#include "stages/thr_mapping.hpp"
#include "thread"
#include "../utils/my_timer.hpp"

// TODO to be removed
#include "../common/file_writer.hpp"

using namespace std;

void thr_impl(const std::string &file_input, const std::string &file_output, int p_degree, bool enable_measures) {
    /**
     * Native Thread implementation.
     */

    // dirty code for checking parallelism degree
    unsigned int p;
    if (p_degree <= 0) {
        p = thread::hardware_concurrency(); // maximum number of threads
    } else {
        p = p_degree;
    }

    // Declaring the timer
    MyTimer timer;

    // STAGE 0: reading
    timer.start("READ");
    auto freq_map = thr_compute_frequencies(file_input, p);
    timer.stop();

    // STAGE 1: build the Huffman tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

    // STAGE 2: Encoding the file into memory
    timer.start("MAP");
    auto encoded_chunks = thr_mapping(huff_map, file_input, p_degree);
    timer.stop();

    // STAGE 3: transform the EncodedChunk to ascii
    timer.start("TRANSFORM");
    // TODO
    timer.stop();


    // STAGE 4: Writing into fs
//    timer.start("WRITING");
//    write_compressed_file(encoded_binary, file_output);
//    timer.stop();

    // other steps goes here...

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }
}