//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_SEQ_TRANSFORM_HPP
#define SPM_PROJECT_SEQ_TRANSFORM_HPP
#include "string"
#include "sstream"

/**
 * @brief Transforms the binary string into ascii-readable string stream.
 * @param binary_string The stream to be transformed
 * @return a stream of ascii characters
 */
std::stringstream seq_transform(std::string& binary_string);

#endif //SPM_PROJECT_SEQ_TRANSFORM_HPP