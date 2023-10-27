//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_FF_FREQ_HPP
#define SPM_PROJECT_FF_FREQ_HPP

#include "../../common/data_types.hpp"
#include "string"

/**
 * Task definition
 */
class FrequencyWorkerTask {
public:
    /**
     * Local frequency map.
     */
    FrequencyMap *f_map;
    /**
     * Index of file_content that indicates the starting point.
     */
    const unsigned long start;

    /**
     * Index of file_content that indicates the ending point.
     */
    const unsigned long stop;

    /**
     * Create a new task for Frequency worker
     * @param s_start Start index
     * @param s_stop Stop index
     */
    explicit FrequencyWorkerTask(const unsigned long s_start, const unsigned long s_stop)
            : f_map(new FrequencyMap()), start(s_start), stop(s_stop) {
        f_map = new FrequencyMap();
    }

};

/**
 * @brief Compute the frequencies for each character in a given input text file.
 * @param file_content the content of the file
 * @param p_degree degree of parallelism
 * @return the computed map of char and its frequency
 */
FrequencyMap ff_compute_frequencies(const std::string &content, unsigned int p_degree);

#endif //SPM_PROJECT_FF_FREQ_HPP
