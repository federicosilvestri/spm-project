//
// Created by federicosilvestri on 18/10/23.
//

#include "ff_impl.hpp"
#include "ff/node.hpp"


#include "string"
#include "../utils/my_timer.hpp"

#include "../common/huffman_map.hpp"
#include "../common/write.hpp"

using namespace std;

void ff_impl(const string &file_input, const string &file_output, bool enable_measures) {
    MyTimer timer;

    // STAGE 0: Reading and computing frequencies
    timer.start("READ");

    timer.stop();

    // STAGE 1: Computing Huffman Tree and Huffman Map
    timer.start("HUFFBUILD");
    //auto huff_tree = build_huffman_tree();
    //auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

    // STAGE 2: Encoding the file into memory
    timer.start("MAP");

    timer.stop();

    // STAGE 3: Transform the binary string to ascii
    timer.start("TRANSFORM");

    timer.stop();

    // STAGE 4: Writing into fs
    timer.start("WRITE");

    timer.stop();


    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }

}