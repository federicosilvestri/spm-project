//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_freq_map.h"
#include "../thr/stages/thr_freq_map.hpp"
#include "../common/huffman_builder.hpp"

#define STATIC_PARALLELISM_DEGREE 4

using namespace std;

int test_functional_reading(string file_input) {
    auto m1 = seq_compute_frequencies(file_input);
    auto m2 = thr_compute_frequencies(file_input, 1);


    CHK_TRUE(m1.size() == m2.size())
    CHK_TRUE(equal(m1.begin(), m1.end(), m2.begin()));

    return 0;
}


int test_huffman_build(string file_input) {
    auto freq_map = seq_compute_frequencies(file_input);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);

    // checking maps
    CHK_TRUE(freq_map.size() == huff_map.size())
    for (auto &p : freq_map) {
        CHK_TRUE(huff_map.contains(p.first));
    }
    for (auto &p : huff_map) {
        CHK_TRUE(freq_map.contains(p.first));
    }

    return 0;
}

void execute_test(int argc, char **argv, string file_input, string file_out) {
    TestSuite test(argc, argv);


    test.doTest("Functional testing for stage: READING", test_functional_reading, file_input);
    test.doTest("Function testing for stafe: HUFF_BUILD", test_huffman_build, file_input);

}