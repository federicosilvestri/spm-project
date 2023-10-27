//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_FF_MAPPING_HPP
#define SPM_PROJECT_FF_MAPPING_HPP

#include "string"
#include "../../common/huffman_builder.hpp"


/**
 * Task definition
 */
class MapperWorkerTask {
public:
    /**
     * Index of file_content that indicates the starting point.
     */
    const unsigned long start;

    /**
     * Index of file_content that indicates the ending point.
     */
    const unsigned long stop;

    /**
     * The index of buffer reserved for the worker.
     */
    const unsigned int buff_index;

    /**
     * Create a new task for mapper.
     * @param s Start index
     * @param e End index
     * @param buff_ind Reserved buffer index
     */
    MapperWorkerTask(const unsigned long s, const unsigned long e, const unsigned int buff_ind) : start(s), stop(e),
                                                                                                  buff_index(buff_ind) {


    }

};

/**
 * @brief Maps the file content of the file into a binary string.
 * @param huff_map The Huffman Map to be used.
 * @param file_content The file content
 * @return A string of binary characters
 */
OutputBuffer ff_mapping(HuffMap &huff_map, const std::string &file_content, unsigned int p_degree);

#endif //SPM_PROJECT_FF_MAPPING_HPP
