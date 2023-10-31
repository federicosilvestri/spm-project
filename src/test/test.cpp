//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_read.hpp"
#include "../thr/stages/thr_read.hpp"
#include "../seq/stages/seq_freq.h"
#include "../thr/stages/thr_freq.hpp"
#include "../common/huffman_builder.hpp"
#include "../seq/stages/seq_mapping.hpp"
#include "../thr/stages/thr_mapping.hpp"

#include "../fastflow//stages/ff_freq.hpp"
#include "../fastflow//stages/ff_mapping.hpp"


#define STATIC_PARALLELISM_DEGREE 5

using namespace std;

SuperThreadPool tp(STATIC_PARALLELISM_DEGREE);

int test_functional_reading(string &file_input) {
    string content1 = thr_read_file(file_input, tp);
    string content2 = seq_read_file(file_input);

    CHK_EQ(content1, content2);

    return 0;
}

int test_functional_calcfreq(string &content) {
    auto m1 = seq_compute_frequencies(content);
    auto m2 = thr_compute_frequencies(content, tp);
    auto m3 = ff_compute_frequencies(content, STATIC_PARALLELISM_DEGREE);

    CHK_TRUE(m1.size() == m2.size() && m2.size() == m3.size());

    for (auto i = 0; i < m1.size(); i++) {
        CHK_EQ(m1[i], m2[i]);
        CHK_EQ(m2[i], m3[i]);
        CHK_EQ(m1[i], m3[i]);
    }

    return 0;
}



int test_huffman_build(string &content) {
    auto freq_map = seq_compute_frequencies(content);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);

    // checking maps
    for (int i = 0; i < freq_map.size(); i++) {
        if (freq_map[i] > 0) {
            CHK_TRUE(huff_map.contains(i));
            CHK_EQ(huff_map.at(i).frequency, freq_map.at(i));
            CHK_TRUE(huff_map.at(i).size > 0);
        }
    }

    return 0;
}

int test_mapping(string &content) {
    auto freq_map = seq_compute_frequencies(content);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);

    auto map_seq = seq_mapping(huff_map, content);
    auto map_thr = thr_mapping(huff_map, content, tp);
    auto map_ff = ff_mapping(huff_map, content, STATIC_PARALLELISM_DEGREE);

    CHK_EQ(map_thr.buffer.size(), map_ff.buffer.size());
    CHK_EQ(map_thr.chunk_info.size(), map_ff.chunk_info.size());

    return 0;
}


void execute_test(int argc, char **argv, string &file_input) {
    TestSuite test(argc, argv);


    // test functional reading
    test.doTest("Functional testing for stage: READ", test_functional_reading, file_input);

    auto file_content = seq_read_file(file_input);
    // test functional calc freq
    test.doTest("Functional testing for stage: FREQCALC", test_functional_calcfreq, file_content);

    // test huffbuild
    test.doTest("Functional testing for stage: HUFFBUILD", test_huffman_build, file_content);

    // test mapping
    test.doTest("Functional testing for stage: MAP", test_mapping, file_content);

}