//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_freq.hpp"
#include "ff/parallel_for.hpp"

FrequencyMap ff_compute_frequencies(const std::string &content, unsigned int p_degree) {
    /*
     * Using a static strategy, because the work is equally complexed.
     */
    FrequencyMap f_map;
    ff::ParallelForReduce<FrequencyMap> instance(p_degree);

    instance.parallel_reduce_static(
            f_map, // Initial value
            FrequencyMap(), // Identify value
            0, // starting index
            content.size(), // ending index
            1, // the loop step
            0, // grain
            /*
             * The mapping function
             */
            [&content](const long i, FrequencyMap &local) {
                int index = static_cast<unsigned char>(content[i]);
                local[index] += 1;
            },
            /*
             * The reduce function
             */
            [](FrequencyMap &f_map, const FrequencyMap& local) {
                for (int i = 0; i < f_map.size(); i++) {
                    f_map[i] += local[i];
                }
            },
            p_degree // number of workers
    );

    return f_map;
}