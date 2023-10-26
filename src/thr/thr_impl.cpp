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
#include "../seq/stages/seq_mapping.hpp" // ONLY TEST

#include "../common/write.hpp"
#include "stages/thr_freq.hpp"
#include "stages/thr_mapping.hpp"

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

    // STAGE 0: READ from file
    timer.start("READ");
    /*
     * Two versions available one that is multithreading, and one that is sequential.
     *
     * PARALLEL:
     * string file_content = thr_read_file(file_input, p_degree);
     * SEQUENTIAL:
     * string file_content = seq_read_file(file_input);
     *
     * Actually the multithreading read is discouraged due to poor performance. If disk is sequential than the fastest
     * algorithm is sequential.
     */
    string file_content = seq_read_file(file_input);
    timer.stop();

    // STAGE 1:
    timer.start("FREQCALC");
    auto freq_map = thr_compute_frequencies(file_content, p_degree);
    timer.stop();


    // STAGE 2: build the Huffman tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();


    // STAGE 3: Encoding the file into memory
    timer.start("MAP");
    auto output_buffer = thr_mapping(huff_map, file_content, p_degree);
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