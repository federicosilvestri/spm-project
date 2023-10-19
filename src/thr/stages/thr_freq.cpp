//
// Created by federicosilvestri on 09/10/23.
//

#include "fstream"
#include "thr_freq.hpp"
#include "vector"
#include "thread"
#include "stdexcept"

using namespace std;


vector<unsigned int> freq_worker(const string &file_content, unsigned int start, unsigned int end) {
    vector<unsigned int> f_map(256, 0);
    for (auto i = start; i <= end; i++) {
        auto v = static_cast<unsigned char>(file_content[i]);
        f_map[v] += 1;
    }

    return f_map;
}

vector<unsigned int> thr_compute_frequencies(const string &file_content, unsigned int p_degree) {
    /*
     * CLASSIC IDEA:
     * Start by splitting file in chunks (arithmetically f_size/p_degree), identified by a couple <start, end> positions.
     * The technique of splitting the work before execute the job is called static strategy.
     * In this case all the task are simple, but we can have unbalanced situations if the p_degree is not
     * divisible by p_degree, but to make it simple I have strongly assumed that is negligible.
     *
     * Each thread reads character by character and creates an HashMap<character, frequency>.
     * when threads has finished the work, I merge the hashmaps. (SEQ?)
     *
     */
    unsigned int f_size = file_content.size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    vector<thread> workers(p_degree);
    vector<vector<unsigned int>> local_maps(p_degree);
    for (unsigned int i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);
        workers[i] = thread(
                [&local_maps, i, &file_content, start, end]() {
                    local_maps[i] = freq_worker(file_content, start, end);
                }
        );
    }

    for (unsigned int i = 0; i < p_degree; i++) {
        // waiting for threads to finish
        workers[i].join();
    }

    /*
     * Now we have to combine the Hashmaps.
     * We know that combine(HM1, HM2) is a binary operation: we can also use than a divide and conquer algorithm.
     */
    vector<unsigned int> reduced = vector<unsigned int>(256, 0);
    for (auto &local_map: local_maps) {
        for (int j = 0; j < local_map.size(); j++) {
            reduced[j] += local_map[j];
        }
    }

    return reduced;
}