//
// Created by federicosilvestri on 09/10/23.
//
#include "thr_impl.hpp"
#include "thread"
#include "../utils/my_timer.hpp"
#include "../utils/logger.hpp"

// Parallel read
#include "stages/thr_read.hpp"
// Sequential read
#include "../seq/stages/seq_read.hpp"

#include "../common/write.hpp"
#include "stages/thr_freq.hpp"
#include "../common/huffman_map.hpp"
#include "stages/thr_mapping.hpp"
#include "stages/thr_transform.hpp"

#include "thread_pool.hpp"

using namespace std;

void thr_impl(const std::string &file_input, const std::string &file_output, int p_degree, bool enable_measures) {
    /**
     * Native Thread implementation.
     */

    // dirty code for checking parallelism degree
    if (p_degree <= 0) {
        p_degree = (int) thread::hardware_concurrency(); // maximum number of threads
    }


    // Declaring the timer
    MyTimer timer;

    // STAGE 0: reading
    timer.start("READ");
//    string file_content = thr_read_file(file_input, p_degree);
    string file_content = seq_read_file(file_input);
    timer.stop();


    timer.start("FREQCALC");
    auto freq_map = thr_compute_frequencies(file_content, p_degree);
    timer.stop();


    // STAGE 1: build the Huffman tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();


    // STAGE 2: Encoding the file into memory
//    timer.start("MAP");
//    auto mapped_stream = thr_mapping(huff_map, &file_content, p_degree);
//    timer.stop();
//
//    //    // STAGE 4: Writing into fs
//    timer.start("WRITE");
//    write_compressed_file(mapped_stream, file_output);
//    timer.stop();

//    // STAGE 3: transform the EncodedChunk to ascii
//    timer.start("TRANSFORM");
//    auto char_stream = thr_transform(mapped_stream, p_degree);
//    timer.stop();
//
//    // STAGE 4: Writing into fs
//    timer.start("WRITE");
//    write_compressed_file(char_stream, file_output);
//    timer.stop();

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }
}