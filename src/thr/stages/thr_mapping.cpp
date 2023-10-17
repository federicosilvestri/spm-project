//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_mapping.hpp"
#include "thread"
#include "../../utils/file_utils.hpp"

using namespace std;

void mapper_worker(HuffMap &huffMap, const string file_input, long start, long end, string &encoded) {
    ifstream fp(file_input);
    fp.seekg(start);
    for (auto i = 0; i <= (end - start); i++) {
        char c;
        fp.get(c);
        encoded.append(huffMap.at(c));
    }
    fp.close();
}


stringstream thr_mapping(HuffMap &huff_map, const string &file_input, unsigned int p_degree) {
    /*
     * We split again the file into chunks, and we assign statically a chunk of data
     * to a thread. The task for each thread is equally complex and the effort of each thread is balanced.
     */
    long f_size = file_size(file_input);
    // adjusting the parallelism, computing chunk size or delta, is the same.
    long chunk_size = f_size / p_degree;
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // a vector of threads.
    vector<thread> threads_c(p_degree);
    // the data where threads puts the results (shared object between threads).
    vector<string> partial_mapped(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        string encoded;
        auto start = i * chunk_size;
        auto end = start + chunk_size - 1;

        if (i == p_degree - 1) {
            // the last thread may be unbalanced, we can use autoscheduling or jobstealing (autoscheduling can be implemented
            // by pushing task inside a queue).
            end = f_size;
            end -= 1;
        }
        partial_mapped[i] = encoded;
        threads_c[i] = thread(mapper_worker, ref(huff_map), file_input, start, end, std::ref(partial_mapped[i]));
    }

    stringstream encoded;
    unsigned int total_size = 0;
    for (auto i = 0; i < p_degree; i++) {
        // waiting for threads to finish
        threads_c[i].join();
        encoded << partial_mapped[i];
        total_size += partial_mapped[i].size();
    }

    if (total_size % 8 != 0) {
        // padding
        unsigned int pad = 8 - (total_size % 8);
        string s(pad, '0');
        encoded << s;
    }

    return encoded;
}