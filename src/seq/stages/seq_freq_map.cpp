//
// Created by Federico Silvestri on 09/10/23.
//
#include "seq_freq_map.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

unordered_map<char, unsigned int> seq_compute_frequencies(const string& file_input) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap (unordered) of char and its own frequency.
     */
    unordered_map<char, unsigned int> frequency_map;
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
        cerr << "Cannot read file!" << endl;
        exit(1);
    }

    /*
    for (auto k : frequency_map) {
        cout << "Char=" << k.first << " Freq=" << k.second << endl;
    }*/


    return frequency_map;
}

