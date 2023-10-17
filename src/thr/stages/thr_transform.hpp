//
// Created by federicosilvestri on 17/10/23.
//

#ifndef SPM_PROJECT_THR_TRANSFORM_HPP
#define SPM_PROJECT_THR_TRANSFORM_HPP
#include "thr_mapping.hpp"
#include "sstream"

/**
 * @brief Transform encoded chunks into a stream of characters.
 * @param encoded_chunks the chunks to be encoded
 * @return character stream
 */
std::stringstream thr_transform(EncodedChunks& encoded_chunks);

#endif //SPM_PROJECT_THR_TRANSFORM_HPP
