//
// Created by Federico Silvestri on 09/10/23.
//
#include "seq_freq.h"
#include <iostream>
#include <unordered_map>

using namespace std;

vector<unsigned int> seq_compute_frequencies(const string *file_content) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap (unordered) of char and its own frequency.
     */
    vector<unsigned int> frequency_map(256, 0);

    for (char key : *file_content) {
        auto v = static_cast<unsigned char>(key);
        frequency_map[v] += 1;
    }

/*
for (auto k : frequency_map) {
    cout << "Char=" << k.first << " Freq=" << k.second << endl;
}*/
    return frequency_map;
}

