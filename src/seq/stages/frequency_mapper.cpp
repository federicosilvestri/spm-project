//
// Created by Federico Silvestri on 09/10/23.
//
#include "frequency_mapper.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

unordered_map<char, unsigned int> compute_frequencies(string file_input) {
    /**
     * Here we start the first stage of algorithm by computing,
     * character by character, an hashmap of char and its own frequency.
     */
    unordered_map<char, unsigned int> frequency_map;
    ifstream file_stream;
    file_stream.open(file_input, ios::in);

    if (file_stream.is_open()) {
        char key;
        while (file_stream.get(key)) {
            cout << key << '\n';
        }
        file_stream.close();
    } else {
        cerr << "Cannot read file!" << endl;
        exit(1);
    }

    return frequency_map;
}

