//
// Created by federicosilvestri on 18/10/23.
//

#include "ff_impl.hpp"
#include "string"
#include "../utils/my_timer.hpp"
#include "../seq/stages/seq_read.hpp"
#include "stages/ff_freq.hpp"
#include "../common/huffman_map.hpp"
#include "stages/ff_mapping.hpp"
//#include "stages/ff_transform.hpp"
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

    // STAGE 2: Computing Huffman Tree and Huffman Map
    timer.start("HUFFBUILD");
    auto huff_tree = build_huffman_tree(f_map);
    auto huff_map = build_huffman_map(huff_tree);
    timer.stop();

//    // STAGE 3: Encoding the file into memory
//    timer.start("MAP");
//    auto mapped_string = ff_mapping(huff_map, file_content, p_degree);
//    timer.stop();

    // STAGE 4: Transform the binary string to ascii
//    timer.start("TRANSFORM");
//    auto binary_steam = ff_transform(mapped_string, p_degree);
//    timer.stop();

    // STAGE 5: Writing into fs
    timer.start("WRITE");

    timer.stop();


    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        timer.print_timings();
    }

}