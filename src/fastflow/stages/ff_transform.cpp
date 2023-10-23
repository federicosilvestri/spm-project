//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_transform.hpp"
#include "ff/parallel_for.hpp"
#include "bitset"
using namespace std;

stringstream ff_transform(string &binary, unsigned int p_degree) {
    ff::ParallelFor instance(p_degree);

    unsigned long block_size = binary.size() / 8;
    unsigned long chunk_size = (block_size / p_degree) + (block_size % p_degree != 0);
    vector<stringstream> locally_transformed(p_degree);

    if (chunk_size < 8) {
        throw invalid_argument("Program should be run sequentially");
    }

    instance.parallel_for_static(
            0,
            p_degree,
            1,
            0,
            [chunk_size, p_degree, &binary, &locally_transformed](const long i) {
                unsigned int begin = i * chunk_size * 8;
                unsigned int end = min(begin + chunk_size * 8, binary.size());

                for (auto j = begin; j < end; j += 8) {
                    bitset<8> group(binary.substr(j, 8));
                    char c = (char) (group.to_ulong() & 0xFF);
                    locally_transformed[i] << c;
                }
            }
    );
    stringstream reduced_stream;
    for (auto &local : locally_transformed) {
        reduced_stream << local.rdbuf();
    }

    return reduced_stream;
}