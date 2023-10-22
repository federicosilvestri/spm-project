//
// Created by federicosilvestri on 09/10/23.
//

#include "fstream"
#include "thr_freq.hpp"
#include "vector"
#include "thread"
#include "functional"

using namespace std;


FrequencyMap freq_worker(const string &file_content, unsigned int start, unsigned int end) {
    FrequencyMap f_map;
    for (auto i = start; i <= end; i++) {
        auto v = static_cast<unsigned char>(file_content[i]);
        f_map[v] += 1;
    }
    return f_map;
}

FrequencyMap
reduce_two_maps(FrequencyMap &m1, FrequencyMap &m2) {
    FrequencyMap reduced;
    auto size = reduced.size();

    for (int i = 0; i < size; i++) {
        reduced[i] += m1[i] + m2[i];
    }
    return reduced;
}


FrequencyMap reduce_maps(vector<FrequencyMap> &maps) {
    if (maps.empty()) {
        throw invalid_argument("maps size cannot be empty!");
    }
    if (maps.size() == 1) {
        return maps[0];
    }

    // compute adjusted size of vector of partially reduced maps.
    auto v_size = (maps.size() % 2 == 0) ? maps.size() : maps.size() - 1;
    // v_size / 2 is the number of possible threads that will be spawned.
    vector<thread> workers(v_size / 2);
    auto reduced_size = (v_size / 2) + (maps.size() % 2 != 0);
    vector<FrequencyMap> reduced(reduced_size);

    for (int i = 0, j = 0; i < v_size; i += 2, j++) {
        auto pFunction = [&reduced, i, j, &maps]() { reduced[j] = reduce_two_maps(maps[i], ref(maps[i + 1])); };
        workers[j] = thread(pFunction);
    }

    // add the results of thread inside the reduced vector.
    for (auto &worker: workers) {
        worker.join();
    }

    if (maps.size() % 2 != 0) {
        reduced[reduced_size - 1] = maps[maps.size() - 1];
    }

    FrequencyMap combined_map = reduce_maps(reduced);
    return combined_map;
}

FrequencyMap thr_compute_frequencies(const string &file_content, unsigned int p_degree) {
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
    vector<FrequencyMap> local_maps(p_degree);
    for (unsigned int i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);
        auto pFunction = [&file_content, start, end, &local_maps, i] {
            local_maps[i] = freq_worker(file_content, start, end);
        };
        workers[i] = thread(pFunction);
    }

    for (unsigned int i = 0; i < p_degree; i++) {
        // waiting for threads to finish
        workers[i].join();
    }

    /*
     * Now we have to combine the Hashmaps.
     * We know that combine(HM1, HM2) is a binary operation: we can also use than a divide and conquer algorithm.
     * TODO: implement it.
     */
//    FrequencyMap reduced;
//    for (auto &local_map: local_maps) {
//        for (int j = 0; j < local_map.size(); j++) {
//            reduced[j] += local_map[j];
//        }
//    }

    return reduce_maps(local_maps);
}