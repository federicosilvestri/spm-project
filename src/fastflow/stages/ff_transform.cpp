//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_transform.hpp"
#include "ff/parallel_for.hpp"

using namespace std;

stringstream ff_transform(string& binary_stream, unsigned int p_degree) {
    stringstream encoded;
    ff::ParallelFor instance(p_degree);

    instance.parallel_reduce_static(
            mapped,
            0,
            file_content.size(),
            1,
            0,
            [&file_content, &huff_map](const long i, string& local) {
                int index = static_cast<unsigned char>(file_content[i]);
                local += huff_map[index];
            },
            [](string &mapped, const string& local) {
                mapped += local;
            },
            p_degree
    );

    return encoded;
}