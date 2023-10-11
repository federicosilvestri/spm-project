//
// Created by federicosilvestri on 09/10/23.
//

#include "thr_impl.hpp"
#include "stages/thr_freq_map.hpp"
#include "thread"
#include "iostream"
#include "chrono"

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

    auto start = chrono::high_resolution_clock::now();
    auto m = thr_compute_frequencies(file_input, p);
    auto reading_time = chrono::high_resolution_clock::now() - start;

    // other steps go here...

    auto total_time = chrono::high_resolution_clock::now() - start;

    /*
     * Managing the output of measures.
     */
    if (enable_measures) {
        cout << "READING=" << reading_time << endl;
        cout << "TOTAL=" << total_time << endl;
    }
}