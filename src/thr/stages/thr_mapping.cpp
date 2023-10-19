//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_mapping.hpp"
#include "thread"
#include "../../utils/file_utils.hpp"

using namespace std;

void mapper_worker(HuffMap &huffMap, const string *file_content, long start, long end, string &encoded) {
    for (auto i = start; i <= end; i++) {
        char c = (*file_content)[i];
        encoded += huffMap[c];
    }
}


string thr_mapping(HuffMap &huff_map, const string *file_content, unsigned int p_degree) {
    /*
     * I split again the file into chunks, and I assign statically a chunk of data
     * to a thread. The task for each thread is equally complex and the effort of each thread is balanced.
     */
    unsigned int f_size = file_content->size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // a vector of threads.
    vector<thread> threads_c(p_degree);
    // the data where threads puts the results (shared object between threads).
    vector<string> local_mapped(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        string encoded;
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);

        local_mapped[i] = encoded;
        threads_c[i] = thread(mapper_worker, ref(huff_map), file_content, start, end, std::ref(local_mapped[i]));
    }

    for (auto &t : threads_c) {
        // waiting for threads
        t.join();
    }

    string binary_string;
    for (const auto & local_string : local_mapped) {
        binary_string += local_string;
    }
    auto padding = 8 - (binary_string.size() % 8);
    string padding_string(padding, '0');
    binary_string.append(padding_string);

    return binary_string;
}