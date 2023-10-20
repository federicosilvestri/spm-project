//
// Created by Federico Silvestri on 09/10/23.
//
#include "seq_freq.h"

using namespace std;

FrequencyMap seq_compute_frequencies(const string *file_content) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap (unordered) of char and its own frequency.
     */
    FrequencyMap f_map;

    for (char key : *file_content) {
        auto v = static_cast<unsigned char>(key);
        f_map[v] += 1;
    }

    return f_map;
}

