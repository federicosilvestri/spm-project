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

using namespace std;

void
freq_worker(const string &file_input, unsigned int start, unsigned int end, unordered_map<char, unsigned int> &f_map) {
    ifstream fp(file_input);
    fp.seekg(start);
    for (auto i = 0; i <= (end - start); i++) {
        char c;
        fp.get(c);

        if (f_map.contains(c)) {
            f_map.at(c) += 1;
        } else {
            f_map.insert({c, 1});
        }
    }
    fp.close();
}

unordered_map<char, unsigned int>
combine_two_map(unordered_map<char, unsigned int> m1, unordered_map<char, unsigned int> m2) {
    unordered_map<char, unsigned int> m3;
    for (auto &p: m1) {
        if (m3.contains(p.first)) {
            m3.at(p.first) += p.second;
        } else {
            m3.insert(p);
        }
    }
    for (auto &p: m2) {
        if (m3.contains(p.first)) {
            m3.at(p.first) += p.second;
        } else {
            m3.insert(p);
        }
    }
    return m3;
}

unordered_map<char, unsigned int> reduce_maps(vector<unordered_map<char, unsigned int>> &maps) {
    if (maps.empty()) {
        throw invalid_argument("maps size cannot be empty!");
    }
    if (maps.size() == 1) {
        return maps[0];
    }

    vector<unordered_map<char, unsigned int>> reduced;
    // compute adjusted size of vector of partially reduced maps.
    auto v_size = (maps.size() % 2 == 0) ? maps.size() : maps.size() - 1;
    // v_size / 2 is the number of possible threads that will be spawned.
    vector<future<unordered_map<char, unsigned int>>> futures_vec(v_size / 2);

    for (int i = 0, j = 0; i < v_size; i += 2, j++) {
        futures_vec[j] = std::async(std::launch::deferred, combine_two_map, maps[i], maps[i + 1]);
    }

    // add the results of thread inside the reduced vector.
    for (auto & fut : futures_vec) {
        reduced.push_back(fut.get());
    }

    if (maps.size() % 2 != 0) {
        reduced.push_back(maps[maps.size() - 1]);
    }

    unordered_map<char, unsigned int> combined_map = reduce_maps(reduced);
    return combined_map;
}

unordered_map<char, unsigned int> thr_compute_frequencies(const string &file_input, unsigned int p_degree) {
    unordered_map<char, unsigned int> m;
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
    // getting file size
    ifstream fp(file_input, ios::binary);
    fp.seekg(0, ios::end);
    // computing chunk size
    auto f_size = fp.tellg();
    fp.close();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = f_size / p_degree;
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // cout << "File is " << f_size << "large";
    vector<thread> threads_c(p_degree);
    vector<unordered_map<char, unsigned int>> vector_maps(p_degree);


    for (auto i = 0; i < p_degree; i++) {
        unordered_map<char, unsigned int> v_map;
        unsigned int start = i * chunk_size;
        unsigned int end = start + chunk_size - 1;

        if (end > f_size) {
            // the last thread may be unbalanced, we can use autoscheduling or jobstealing (autoscheduling can be implemented
            // by pushing task inside a queue).
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