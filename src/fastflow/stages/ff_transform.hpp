//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_FF_TRANSFORM_HPP
#define SPM_PROJECT_FF_TRANSFORM_HPP
#include "string"

/**
 * @brief Transform stream of binary data into ascii characters.
 * @param binary the chunks to be encoded
 * @param p_degree the degree of parallelism
 * @return character stream
 */
std::string ff_transform(const std::string& binary, unsigned int p_degree);

#endif //SPM_PROJECT_FF_TRANSFORM_HPP
