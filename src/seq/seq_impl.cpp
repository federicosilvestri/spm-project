//
// Created by Federico Silvestri on 09/10/23.
//

#include "seq_impl.hpp"
#include "stages/seq_freq_map.h"
#include "string"
#include "chrono"

using namespace std;

void seq_impl(const string& file_input, const string& file_output, bool enable_measures) {
    auto start = chrono::high_resolution_clock::now();
    auto m = seq_compute_frequencies(file_input);
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