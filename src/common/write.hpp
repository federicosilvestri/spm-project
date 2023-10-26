//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_WRITE_HPP
#define SPM_PROJECT_WRITE_HPP
#include "string"
#include "sstream"
#include "../common/data_types.hpp"

/**
 * @brief Write the OutputBuffer inside the file
 * @param out_buff the filled buffer
 * @param file_output the path of output file.
 */
void write_compressed_file(OutputBuffer& out_buff, const std::string &file_output);

#endif //SPM_PROJECT_WRITE_HPP
