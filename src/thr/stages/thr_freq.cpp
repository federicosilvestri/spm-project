//
// Created by federicosilvestri on 09/10/23.
//

#include "fstream"
#include "thr_freq.hpp"
#include "vector"
#include "functional"
#include "thread"
#include "future"
#include "stdexcept"

using namespace std;


void
freq_worker(const string *file_content, unsigned int start, unsigned int end, FrequencyMap *f_map) {
    for (auto i = start; i <= end; i++) {
        char c = (*file_content)[i];

        if (f_map->contains(c)) {
            f_map->at(c)++;
        } else {
            f_map->insert({c, 1});
        }
    }
}

FrequencyMap *
reduce_two_maps(FrequencyMap *m1, FrequencyMap *m2) {
    auto *m3 = new unordered_map<char, unsigned int>;
    for (auto &p: *m1) {
        if (m3->contains(p.first)) {
            m3->at(p.first) += p.second;
        } else {
            m3->insert(p);
        }
    }
    for (auto &p: *m2) {
        if (m3->count(p.first)) {
            m3->at(p.first) += p.second;
        } else {
            m3->insert(p);
        }
    }
    return m3;
}

FrequencyMap reduce_maps(vector<FrequencyMap *> &maps) {
    if (maps.empty()) {
        throw invalid_argument("maps size cannot be empty!");
    }
    if (maps.size() == 1) {
        return *maps[0];
    }

    vector<FrequencyMap *> reduced;
    // compute adjusted size of vector of partially reduced maps.
    auto v_size = (maps.size() % 2 == 0) ? maps.size() : maps.size() - 1;
    // v_size / 2 is the number of possible threads that will be spawned.
    vector<future<FrequencyMap *>> futures_vec(v_size / 2);

    for (int i = 0, j = 0; i < v_size; i += 2, j++) {
        futures_vec[j] = std::async(std::launch::deferred, reduce_two_maps, ref(maps[i]), ref(maps[i + 1]));
    }

    // add the results of thread inside the reduced vector.
    for (auto &fut: futures_vec) {
        reduced.push_back(fut.get());
    }

    if (maps.size() % 2 != 0) {
        reduced.push_back(maps[maps.size() - 1]);
    }

    FrequencyMap combined_map = reduce_maps(reduced);
    return combined_map;
}

FrequencyMap thr_compute_frequencies(const string *file_content, unsigned int p_degree) {
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
    unsigned int f_size = file_content->size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    vector<thread> threads_c(p_degree);
    std::vector<FrequencyMap *> local_maps(p_degree);

    for (unsigned int i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);

        local_maps[i] = new FrequencyMap();
        //cout << "start job " << i << endl;
        threads_c[i] = thread{freq_worker, file_content, start, end, local_maps[i]};
    }

    for (unsigned int i = 0; i < p_degree; i++) {
        // waiting for threads to finish
        //cout << "waiting job " << i << endl;
        threads_c[i].join();
    }

    /*
     * Now we have to combine the Hashmaps.
     * We know that combine(HM1, HM2) is a binary operation: we can also use than a divide and conquer algorithm.
     */
    return reduce_maps(local_maps);
}