//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_transform.hpp"
#include "vector"
#include "future"
#include "bitset"

using namespace std;

std::stringstream transform_worker(std::string &binary_string) {
    stringstream ss;
    for (int i = 0; i < binary_string.length(); i += 8) {
        bitset<8> group(binary_string.substr(i, 8));
        char c = (char) (group.to_ulong() & 0xFF);
        ss << c;

    }
    return ss;
}


stringstream thr_transform(EncodedChunks &encoded_chunks) {
    /*
     * For each chunk start a thread and transform the string into encoded ascii string.
     * Finally, merge the result sequentially by inserting the string inside the stringstream.
     */
    vector<future<stringstream>> futures(encoded_chunks.chunks.size());

    // starting threads
    for (auto i = 0; i < futures.size(); i++) {
        futures[i] = async(launch::async, transform_worker, ref(encoded_chunks.chunks[i]));
    }

    // collecting futures value and merge the result into the stream
    stringstream final_stream;
    for (auto &fut: futures) {
        stringstream tmp = fut.get();
        final_stream << tmp.rdbuf();
    }

    return final_stream;
}