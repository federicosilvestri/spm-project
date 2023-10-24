//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_transform.hpp"
#include "vector"
#include "thread"
#include "bitset"

using namespace std;

void transform_worker(std::string &binary_string, unsigned int begin, unsigned int end, string& ss, unsigned int ss_begin) {
    for (unsigned int i = begin, j = ss_begin; i < end; i += 8, j += 1) {
        bitset<8> group(binary_string.substr(i, 8));
        char c = (char) (group.to_ulong() & 0xFF);
        ss[j] = c;
    }
}


stringstream thr_transform(string &binary, unsigned int p_degree) {
    /*
     * We define a chunk size for each thread that must be a multiple of 8.
     * For each chunk start a thread and transform the string into encoded ascii string.
     * Finally, merge the result sequentially by inserting the string inside the stringstream.
     */
    unsigned long block_size = binary.size() / 8;
    unsigned long chunk_size = (block_size / p_degree) + (block_size % p_degree != 0);

    if (chunk_size < 8) {
        throw invalid_argument("Program should be run sequentially");
    }

    vector<thread> workers(p_degree);
    // Preallocate the mapped string
    string mapped(block_size, '\0');

    // starting threads
    for (auto i = 0; i < p_degree; i++) {
        unsigned int begin = i * chunk_size * 8;
        unsigned int end = min(begin + chunk_size * 8, binary.size());
        unsigned int ss_begin = i * chunk_size;

        auto pFunction = [begin, end, ss_begin, &binary, &mapped]() {
            transform_worker(binary, begin, end, mapped, ss_begin);
        };
        workers[i] = thread(pFunction);
    }

    // collecting futures value and merge the result into the stream
    for (auto &worker: workers) {
        worker.join();
    }

    stringstream final_stream;
    final_stream << mapped;

    return final_stream;
}