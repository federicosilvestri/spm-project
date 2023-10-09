//
// Created by Federico Silvestri on 07/10/23.
//
#include <iostream>
#include "string"
#include "utils/file_utils.hpp"

#include "seq/seq_impl.hpp"

using namespace std;

void print_usage() {
    cout << "Usage: huffman_enc SEQ|THR|FF <input_filepath> <output_filepath> [PAR_DEGREE: int]" << endl;
    cout << "\tSEQ: is the sequential implementation," << endl;
    cout << "\tTHR: is the parallelized version using thread pools," << endl;
    cout << "\tFF: it the parallelized version using FastFlow." << endl;
}

int main(int argc, char* argv[]) {
    /*
     * The main is a simple switch between implementations.
     */
    if (argc < 4) {
        print_usage();
        return 1;
    }

    // Checking second and third argument (input and output files)
    string in_file = string(argv[2]);
    string out_file = string(argv[3]);

    // Checking if input file exists
    if (!file_exists(in_file)) {
        cerr << "The file " << in_file << " does not exist." << endl;
        return 1;
    }

    if (file_exists(out_file)) {
        cout << "The file " << out_file << " already exist, overwriting it by default" << endl;
    }

    // checking the parallelism degree input
    int parallelism_degree = -1; // default value (it will be handled by implementations)
    if (argc == 5) {
        try {
            parallelism_degree = stoi(argv[4]);
        } catch (...) {
            cerr << "The parallelism degree must be a number!" << endl;
            return 1;
        }
        if (parallelism_degree <= 0) {
            cerr << "The parallelism degree must be a number greater than 0!" << endl;
            return 1;
        }

        cout << "Using PAR_DEGREE=" << parallelism_degree << endl;
    }


    // Checking first argument before starting (parallelization method)
    string par_choice = argv[1];
    if ("SEQ" == par_choice) {
        cout << "Starting SEQ execution" << endl;
        seq_impl(in_file, out_file);
    } else if ("THR" == par_choice) {
        cout << "Starting THR implementation execution" << endl;
    } else if ("FF" == par_choice) {
        cout << "Starting FF implementation execution" << endl;
    } else {
        cerr << "The parallelization method is not supported." << endl;
        print_usage();
    }

    return 0;
}

