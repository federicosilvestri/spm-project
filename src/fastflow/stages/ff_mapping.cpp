//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_mapping.hpp"
#include "ff/parallel_for.hpp"

using namespace std;

std::string ff_mapping(HuffMap &huff_map, const std::string &file_content, unsigned int p_degree) {
    string mapped;
    ff::ParallelForReduce<string> instance(p_degree);

    instance.parallel_reduce_static(
            mapped,
            "",
            0,
            file_content.size(),
            1,
            0,
            [&file_content, &huff_map](const long i, string &local) {
                int index = static_cast<unsigned char>(file_content[i]);
                local += huff_map[index];
            },
            [](string &mapped, const string &local) {
                mapped += local;
            }
    );

    auto padding = string((mapped.size() % 8), '0');
    mapped += padding;
    return mapped;
}