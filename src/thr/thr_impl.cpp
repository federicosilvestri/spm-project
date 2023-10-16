//
// Created by federicosilvestri on 09/10/23.
//

#include "thr_impl.hpp"
#include "stages/thr_freq_map.hpp"
#include "../common/huffman_map.hpp"
#include "thread"
#include "../utils/my_timer.hpp"

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
    timer.start("READING");
    auto freq_map = thr_compute_frequencies(file_input, p);
    timer.stop();

    // STAGE 1: build the Huffman tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

    // other steps goes here...

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }
}