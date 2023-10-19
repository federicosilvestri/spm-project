//
// Created by federicosilvestri on 19/10/23.
//
#include "seq_read.hpp"
#include "fstream"
#include "sstream"
#include "../../utils/file_utils.hpp"

using namespace std;

string seq_read_file(const string &file_input) {
    std::ifstream fp(file_input, ios::in);

    if (!fp.is_open()) {
        throw std::invalid_argument("Cannot open the file for reading!");
    }

    auto f_size = file_size(file_input);
    string data(f_size, '\0');
    fp.read(&data[0], f_size);

    /*
     * Another possible implementation with streams, but it will slow down the performance.
     * std::stringstream content;
     * content << fp.rdbuf();
     * std::string data = content.str();
    */

    fp.close();
    return data;
}
