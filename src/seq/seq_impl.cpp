//
// Created by Federico Silvestri on 09/10/23.
//

#include "seq_impl.hpp"
#include "stages/seq_freq_map.h"
#include "string"
#include "chrono"

using namespace std;

void seq_impl(const string& file_input, const string& file_output) {
    auto start = chrono::high_resolution_clock::now();
    auto m = seq_compute_frequencies(file_input);
    auto elapsed = chrono::high_resolution_clock::now() - start;
    auto end = chrono::high_resolution_clock::now() - start;

    for (auto &g : m) {
        cout << "CHAR=" << g.first << " FREQ=" << g.second << endl;
    }

    cout << "SEQ reading in " << elapsed << endl;
}