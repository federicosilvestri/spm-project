//
// Created by federicosilvestri on 09/10/23.
//

#include "iostream"
#include "fstream"
#include "thr_freq_map.hpp"
#include "vector"
#include "functional"
#include "thread"
#include "future"
#include "stdexcept"

#include "../../utils/file_utils.hpp"

using namespace std;

void
freq_worker(const string &file_input, unsigned int start, unsigned int end, FrequencyMap &f_map) {
    ifstream fp(file_input);
    fp.seekg(start);
    for (auto i = 0; i <= (end - start); i++) {
        char c;
        fp.get(c);

        if (f_map.count(c)) {
            f_map.at(c) += 1;
        } else {
            f_map.insert({c, 1});
        }
    }
    fp.close();
}

FrequencyMap
reduce_two_maps(FrequencyMap &m1, FrequencyMap &m2) {
    unordered_map<char, unsigned int> m3;
    for (auto &p: m1) {
        if (m3.count(p.first)) {
            m3.at(p.first) += p.second;
        } else {
            m3.insert(p);
        }
    }
    for (auto &p: m2) {
        if (m3.count(p.first)) {
            m3.at(p.first) += p.second;
        } else {
            m3.insert(p);
        }
    }
    return m3;
}

FrequencyMap reduce_maps(FrequencyVector &maps) {
    if (maps.empty()) {
        throw invalid_argument("maps size cannot be empty!");
    }
    if (maps.size() == 1) {
        return maps[0];
    }

    FrequencyVector reduced;
    // compute adjusted size of vector of partially reduced maps.
    auto v_size = (maps.size() % 2 == 0) ? maps.size() : maps.size() - 1;
    // v_size / 2 is the number of possible threads that will be spawned.
    vector<future<FrequencyMap>> futures_vec(v_size / 2);

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

FrequencyMap thr_compute_frequencies(const string &file_input, unsigned int p_degree) {
    FrequencyMap m;
#ifdef GMR
    /*
     * GOOGLE MAP REDUCE SIMPLE IDEA:
     * divido il file in tanti chunk, essenzialmente se il file è grande 100 e ho 5 thread,
     * divido il file in 5 parti e lo do in pasto a 5 mapper (che fanno anche la fusion rule)
     * gli altri thread, in particolare i reducer vengono creati e rimangono in attesa di ricevere
     * <k, c> dagli altri, e possono essere anche...
     */
#else
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
    long f_size = file_size(file_input);
    // adjusting the parallelism, computing chunk size or delta, is the same.
    long chunk_size = f_size / p_degree;
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    vector<thread> threads_c(p_degree);
    FrequencyVector vector_maps(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        unordered_map<char, unsigned int> v_map;
        auto start = i * chunk_size;
        auto end = start + chunk_size - 1;

        if (i == p_degree - 1) {
            // the last thread may be unbalanced, we can use autoscheduling or jobstealing (autoscheduling can be implemented
            // by pushing task inside a queue).
            end = f_size;
            end -= 1;
        }
        vector_maps[i] = v_map;
        threads_c[i] = thread(freq_worker, file_input, start, end, std::ref(vector_maps[i]));
    }

    for (auto i = 0; i < p_degree; i++) {
        // waiting for threads to finish
        threads_c[i].join();
    }

    /*
     * Now we have to combine the Hashmaps.
     * We know that combine(HM1, HM2) is a binary operation: we can use than a divide and conquer algorithm.
     */

    m = reduce_maps(vector_maps);

#endif

    return m;
}