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
     * Constant file content.
     */
    const std::string &file_content;
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

    explicit FrequencyWorkerTask(const std::string &f_c, const unsigned long s_start, const unsigned long s_stop)
            : file_content(f_c), f_map(new FrequencyMap()), start(s_start), stop(s_stop) {
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
