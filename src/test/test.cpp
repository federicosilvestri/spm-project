//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_freq_map.h"
#include "../thr/stages/thr_freq_map.hpp"
#include "../common/huffman_map.hpp"
#include "../seq/stages/seq_mapping.hpp"

#define STATIC_PARALLELISM_DEGREE 5

using namespace std;


int test_functional_reading(string &file_input) {
    auto m1 = seq_compute_frequencies(file_input);
    auto m2 = thr_compute_frequencies(file_input, STATIC_PARALLELISM_DEGREE);

    CHK_TRUE(m1.size() == m2.size());

    // double check
    for (auto &p : m1) {
        CHK_TRUE(m2.count(p.first));
        CHK_TRUE(m2.at(p.first) == p.second)
    }
    for (auto &p : m2) {
        CHK_TRUE(m1.count(p.first));
        CHK_TRUE(m1.at(p.first) == p.second)
    }

    return 0;
}


int test_huffman_build(string &file_input) {
    auto freq_map = seq_compute_frequencies(file_input);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);

    // checking maps
    CHK_TRUE(freq_map.size() == huff_map.size())
    for (auto &p: freq_map) {
        CHK_TRUE(huff_map.count(p.first));
    }
    for (auto &p: huff_map) {
        CHK_TRUE(freq_map.count(p.first));
    }

    return 0;
}

int test_huffman_encoding(string &file_input) {
    auto freq_map = seq_compute_frequencies(file_input);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto encoded_bin = seq_mapping(huff_map, file_input);

    CHK_EQ(encoded_bin.size() % 8, 0);

    return 0;
}

void execute_test(int argc, char **argv, string &file_input, string &file_out) {
    TestSuite test(argc, argv);

    test.doTest("Functional testing for stage: READING", test_functional_reading, file_input);
    test.doTest("Functional testing for stage: HUFFBUILD", test_huffman_build, file_input);
    test.doTest("Functional testing for stage: ENCODING", test_huffman_encoding, file_input);

}