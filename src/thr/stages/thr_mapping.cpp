//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_mapping.hpp"
#include "thread"
#include "../../utils/file_utils.hpp"

using namespace std;

string mapper_worker(HuffMap &huffMap, const string &file_content, long start, long end) {
    string encoded = "";
    for (auto i = start; i <= end; i++) {
        char c = file_content[i];
        encoded += huffMap[c].code;
    }
    return encoded;
}


string thr_mapping(HuffMap &huff_map, const string &file_content, unsigned int p_degree) {
    /*
     * I split again the file into chunks, and I assign statically a chunk of data
     * to a thread. The task for each thread is equally complex and the effort of each thread is balanced.
     */
    unsigned int f_size = file_content.size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // a vector of threads.
    vector<thread> workers(p_degree);
    // the data where threads puts the results (shared object between threads).
    vector<string> local_mapped(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);

        auto pFunction = [&local_mapped, i, start, end, &file_content, &huff_map]() {
            local_mapped[i] = mapper_worker(huff_map, file_content, start, end);
        };

        workers[i] = thread(pFunction);
    }

    string binary_string;
    for (auto i = 0; i < workers.size(); i++) {
        // waiting for threads
        workers[i].join();
        binary_string += local_mapped[i];
    }

    auto padding = 8 - (binary_string.size() % 8);
    string padding_string(padding, '0');
    binary_string += padding_string;

    return binary_string;
}