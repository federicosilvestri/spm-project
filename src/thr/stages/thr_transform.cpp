//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_transform.hpp"
#include "vector"
#include "future"
#include "bitset"

using namespace std;

stringstream transform_worker(std::string &binary_string, unsigned int begin, unsigned int end) {
    stringstream ss;
    for (auto i = begin; i < end; i += 8) {
        bitset<8> group(binary_string.substr(i, 8));
        char c = (char) (group.to_ulong() & 0xFF);
        ss << c;
    }
    return ss;
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
    vector<future<stringstream>> futures(p_degree);

    // starting threads
    for (auto i = 0; i < p_degree; i++) {
        unsigned int begin = i * chunk_size * 8;
        unsigned int end = min(begin + chunk_size * 8, binary.size());

        futures[i] = async(launch::async, transform_worker, ref(binary), begin, end);
    }

    // collecting futures value and merge the result into the stream
    stringstream final_stream;
    for (auto &fut: futures) {
        stringstream tmp = fut.get();
        final_stream << tmp.rdbuf();
    }

    return final_stream;
}