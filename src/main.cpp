//
// Created by Federico Silvestri on 07/10/23.
//
#include <iostream>
#include "string"
#include "test/test_common.h"
#include "utils/file_utils.hpp"
#include "utils/logger.hpp"

#include "seq/seq_impl.hpp"
#include "thr/thr_impl.hpp"

// define the logging level, default to debug
#define LOGGING_LEVEL "DEBUG"

using namespace std;

void print_usage(const string &prg_name) {
    cout << "Usage: " << prg_name << " SEQ|THR|FF|-T <input_filepath> <output_filepath> <PAR_DEGREE: int> [-M]" << endl;
    cout << "\tSEQ: is the sequential implementation (you should set PAR_DEGREE=0)," << endl;
    cout << "\tTHR: is the parallelized version using thread pools," << endl;
    cout << "\tFF: it the parallelized version using FastFlow." << endl;
    cout << "\t-T: is a special command that executes functional tests." << endl << endl;
    cout << "\t<input_filepath> is the file to compress." << endl;
    cout << "\t<output_filepath> is the file to produce as compressed output." << endl << endl;
    cout << "\tPAR_DEGREE is the parallelization degree that you want to use," << endl;
    cout << "\t\tuse 0 for maximum degree or auto select." << endl;
    cout << "\t-M enables the program to send to stdout the execution time." << endl;
}

int main(int argc, char *argv[]) {
    /*
     * The main is a simple switch between implementations.
     */
    if (argc < 5) {
        print_usage(string(argv[0]));
        return 1;
    }

    // creating and initializing the logger object
    auto logger = Logger::GetInstance();
    auto log_level = logger->GetLogLevel(LOGGING_LEVEL);
    logger->SetLogPreferences(log_level);

    // Checking second and third argument (input and output files)
    string in_file = string(argv[2]);
    string out_file = string(argv[3]);

    // Checking if input file exists
    if (!file_exists(in_file)) {
        cerr << "The file " << in_file << " does not exist." << endl;
        return 1;
    }

    if (file_exists(out_file)) {
        logger->Log("The file already exist, overwriting it by default", LogLevel::DEBUG);
    }

    // checking the parallelism degree input from user argument
    int parallelism_degree;

    try {
        parallelism_degree = stoi(argv[4]);
    } catch (...) {
        cerr << "The parallelism degree must be a number!" << endl;
        return 1;
    }
    if (parallelism_degree < 0) {
        cerr << "The parallelism degree must be a number greater or equal than 0!" << endl;
        return 1;
    }

    logger->Log("User input PAR_DEGREE=" + to_string(parallelism_degree), LogLevel::DEBUG);

    if (string(argv[1]) == "-T") {
        // Special execution, it executes the internal FUNCTIONAL tests.
        execute_test(argc, argv, in_file, out_file);
        return 0;
    }

    bool enable_measures = false;
    if (argc == 6 && string(argv[5]) == "-M") {
        // enable measurements
        enable_measures = true;
    }

    // Checking first argument before starting (parallelization method)
    string par_choice = argv[1];
    if ("SEQ" == par_choice) {
        logger->Log("Starting SEQ execution", LogLevel::DEBUG);
        seq_impl(in_file, out_file, enable_measures);
    } else if ("THR" == par_choice) {
        logger->Log("Starting THR implementation execution", LogLevel::DEBUG);
        thr_impl(in_file, out_file, parallelism_degree, enable_measures);
    } else if ("FF" == par_choice) {
        logger->Log("Starting FF implementation execution", LogLevel::DEBUG);
        return 1; // not yet implemented
    } else {
        cerr << "The parallelization method is not supported." << endl;
        print_usage(string(argv[0]));
    }

    return 0;
}

