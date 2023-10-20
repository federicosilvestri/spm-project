//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_TRANSFORM_HPP
#define SPM_PROJECT_THR_TRANSFORM_HPP
#include "thr_mapping.hpp"
#include "sstream"

/**
 * @brief Transform stream of binary data into ascii characters.
 * @param binary_stream the chunks to be encoded
 * @param p_degree the degree of parallelism
 * @return character stream
 */
std::stringstream thr_transform(std::string& binary_stream, unsigned int p_degree);

#endif //SPM_PROJECT_THR_TRANSFORM_HPP
