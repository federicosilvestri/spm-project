//
// Created by Federico Silvestri on 09/10/23.
//
#include "seq_freq_map.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

FrequencyMap seq_compute_frequencies(const string &file_input) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap (unordered) of char and its own frequency.
     */
    FrequencyMap frequency_map;
    ifstream file_stream;
    file_stream.open(file_input, ios::in);

    if (file_stream.is_open()) {
        char key;
        while (file_stream.get(key)) {
            if (frequency_map.count(key)) {
                frequency_map.at(key) += 1;
            } else {
                frequency_map.insert({key, 1});
            }
        }
        file_stream.close();
    } else {
        throw invalid_argument("Cannot read the input file!");
    }

    /*
    for (auto k : frequency_map) {
        cout << "Char=" << k.first << " Freq=" << k.second << endl;
    }*/


    return frequency_map;
}

