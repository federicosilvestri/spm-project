//
// Created by federicosilvestri on 19/10/23.
//

#include "thr_read.hpp"
#include "../../utils/file_utils.hpp"
#include "fstream"
#include "thread"
#include "vector"

using namespace std;

void file_read_worker(const string &input_file, string &buffer, unsigned long start, unsigned long stop) {
    ifstream fp(input_file, ios::binary | ios::in);

    if (!fp.is_open()) {
        throw invalid_argument("Cannot open the file!");
    }
    fp.seekg(start);
    fp.read(&buffer[start], stop - start);
    fp.close();
}

string thr_read_file(const string &input_file, SuperThreadPool &thread_pool) {
    // compute the file size
    auto f_size = file_size(input_file);
    // create new large buffer that contains all file inside the memory (memory expensive operation)
    string data(f_size, '\0');
    // slit the file into the fairest number possible, rounding to next value.
    size_t chunk_size = f_size / thread_pool.get_nw() + (f_size % thread_pool.get_nw() != 0);

    // pushing threads
    for (auto i = 0; i < thread_pool.get_nw(); i++) {
        auto start = i * chunk_size; // the start position
        auto end = min(f_size, start + chunk_size); // the minimum between the file size and
        auto pFunction = [&input_file, &data, start, end]() {
            file_read_worker(input_file, ref(data), start, end);
        };
        thread_pool.submit(pFunction);
    }

    thread_pool.wait_all();

    return data;
}