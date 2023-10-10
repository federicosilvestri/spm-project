//
// Created by federicosilvestri on 10/10/23.
//
#include "test_common.h"
#include "../seq/stages/seq_freq_map.h"
#include "../thr/stages/thr_freq_map.hpp"

#define STATIC_PARALLELISM_DEGREE 4

using namespace std;

int test_functional_reading(string file_input) {
    auto m1 = seq_compute_frequencies(file_input);
    auto m2 = thr_compute_frequencies(file_input, 1);


    return m1.size() == m2.size() && equal(
            m1.begin(), m1.end(), m2.begin()
    );
}

void execute_test(int argc, char **argv, string file_input, string file_out) {
    TestSuite test(argc, argv);


    test.doTest("Functional testing for stage: READING", test_functional_reading, file_input);
    //test.doTest("simple arguments example", simple_args_example, 1, "1");
    //test.doTest("test directory example", test_directory_example);
}