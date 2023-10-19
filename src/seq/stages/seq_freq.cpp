//
// Created by Federico Silvestri on 09/10/23.
//
#include "seq_freq.h"
#include <iostream>
#include <unordered_map>

using namespace std;

FrequencyMap seq_compute_frequencies(const string *file_content) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap (unordered) of char and its own frequency.
     */
    FrequencyMap frequency_map;

    for (char key: *file_content) {
        if (frequency_map.contains(key)) {
            frequency_map[key]++;
        } else {
            frequency_map.insert({key, 1});
        }
    }

/*
for (auto k : frequency_map) {
    cout << "Char=" << k.first << " Freq=" << k.second << endl;
}*/
    return frequency_map;
}

