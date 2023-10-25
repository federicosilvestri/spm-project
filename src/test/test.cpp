//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_read.hpp"
#include "../thr/stages/thr_read.hpp"
#include "../seq/stages/seq_freq.h"
#include "../thr/stages/thr_freq.hpp"
#include "../common/huffman_map.hpp"
#include "../seq/stages/seq_mapping.hpp"
#include "../thr/stages/thr_mapping.hpp"
#include "../thr/stages/thr_transform.hpp"


#define STATIC_PARALLELISM_DEGREE 5

using namespace std;


int test_functional_reading(string &file_input) {
    string content1 = thr_read_file(file_input, STATIC_PARALLELISM_DEGREE);
    string content2 = seq_read_file(file_input);

    CHK_EQ(content1, content2);

    return 0;
}

int test_functional_calcfreq(string &file_input) {
    string content = seq_read_file(file_input);
    auto m1 = seq_compute_frequencies(content);
    auto m2 = thr_compute_frequencies(content, STATIC_PARALLELISM_DEGREE);

    CHK_TRUE(m1.size() == m2.size());

    for (auto i = 0; i < m1.size(); i++) {
        CHK_EQ(m1[i], m2[i]);
    }

    return 0;
}


int test_huffman_build(string &file_input) {
    string content = seq_read_file(file_input);
    auto freq_map = seq_compute_frequencies(content);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);

    // checking maps
    for (int i = 0; i < freq_map.size(); i++) {
        if (freq_map[i] > 0) {
            CHK_TRUE(huff_map.contains(i));
        }
    }

    return 0;
}

int test_mapping(string &file_input) {
    string content = seq_read_file(file_input);
    auto freq_map = seq_compute_frequencies(content);
    auto huff_tree = build_huffman_tree(freq_map);
    auto huff_map = build_huffman_map(huff_tree);
    auto mapped_bin = seq_mapping(huff_map, content);
    auto mapped_bin2 = thr_mapping(huff_map, content, STATIC_PARALLELISM_DEGREE);

    CHK_EQ(mapped_bin.size() % 8, 0); // non ha senso perché sono già ottetti
    CHK_EQ(mapped_bin2.size() % 8, 0); // non ha senso perché sono già ottetti
    CHK_TRUE(mapped_bin == mapped_bin2);
    return 0;
}


void execute_test(int argc, char **argv, string &file_input) {
    TestSuite test(argc, argv);

    test.doTest("Functional testing for stage: READ", test_functional_reading, file_input);
    test.doTest("Functional testing for stage: FREQCALC", test_functional_calcfreq, file_input);
    test.doTest("Functional testing for stage: HUFFBUILD", test_huffman_build, file_input);
    test.doTest("Functional testing for stage: MAP", test_mapping, file_input);

}