//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_freq_map.h"
#include "../thr/stages/thr_freq_map.hpp"
#include "../common/huffman_map.hpp"
#include "../seq/stages/seq_mapping.hpp"
#include "../thr/stages/thr_mapping.hpp"
#include "../seq/stages/seq_transform.hpp"
#include "../thr/stages/thr_transform.hpp"


#define STATIC_PARALLELISM_DEGREE 5

using namespace std;


int test_functional_reading(string &file_input) {
    auto m1 = seq_compute_frequencies(file_input);
    auto m2 = thr_compute_frequencies(file_input, STATIC_PARALLELISM_DEGREE);

    CHK_TRUE(m1.size() == m2.size());

    // double check
    for (auto &p: m1) {
        CHK_TRUE(m2.count(p.first));
        CHK_TRUE(m2.at(p.first) == p.second)
    }
    for (auto &p: m2) {
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

int test_mapping(string &file_input) {
    auto freq_map = seq_compute_frequencies(file_input);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto mapped_bin = seq_mapping(huff_map, file_input);
    auto mapped_bin2 = thr_mapping(huff_map, file_input, STATIC_PARALLELISM_DEGREE);

    CHK_EQ(mapped_bin.size() % 8, 0);
    CHK_EQ(mapped_bin2.str().size() % 8, 0);

    CHK_TRUE(mapped_bin.size() == mapped_bin2.str().size());
    return 0;
}

int test_transform(string &file_input) {
    auto freq_map = seq_compute_frequencies(file_input);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto mapped_bin = seq_mapping(huff_map, file_input);
    auto mapped_bin2 = thr_mapping(huff_map, file_input, STATIC_PARALLELISM_DEGREE);
    auto stream_seq = seq_transform(mapped_bin);
    auto stream_thr = thr_transform(mapped_bin2, STATIC_PARALLELISM_DEGREE);

    char c1, c2;
    while (stream_seq.get(c1) && stream_thr.get(c2)) {
        CHK_EQ(c1, c2);
    }


    return 0;
}

void execute_test(int argc, char **argv, string &file_input) {
    TestSuite test(argc, argv);

    test.doTest("Functional testing for stage: READ", test_functional_reading, file_input);
    test.doTest("Functional testing for stage: HUFFBUILD", test_huffman_build, file_input);
    test.doTest("Functional testing for stage: MAP", test_mapping, file_input);
    test.doTest("Functional testing for stage: TRANSFORM", test_transform, file_input);

}