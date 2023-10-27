//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_TRANSFORM_HPP
#define SPM_PROJECT_THR_TRANSFORM_HPP
#include "thr_mapping.hpp"
#include "../../utils/thread_pool.hpp"
#include "sstream"

/**
 * @brief Transform stream of binary data into ascii characters.
 * @param binary_stream the chunks to be encoded
 * @param tp Thread Pool
 * @return character stream
 */
std::stringstream thr_transform(std::string& binary_stream, SuperThreadPool& tp);

#endif //SPM_PROJECT_THR_TRANSFORM_HPP
