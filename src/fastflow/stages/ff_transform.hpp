//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_FF_TRANSFORM_HPP
#define SPM_PROJECT_FF_TRANSFORM_HPP
#include "sstream"
#include "string"

/**
 * @brief Transform stream of binary data into ascii characters.
 * @param binary_stream the chunks to be encoded
 * @param p_degree the degree of parallelism
 * @return character stream
 */
std::stringstream ff_transform(std::string& binary_stream, unsigned int p_degree);

#endif //SPM_PROJECT_FF_TRANSFORM_HPP