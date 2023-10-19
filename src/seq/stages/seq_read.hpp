//
// Created by federicosilvestri on 19/10/23.
//

#ifndef SPM_PROJECT_SEQ_READ_HPP
#define SPM_PROJECT_SEQ_READ_HPP

#include "string"

/**
 * @brief Read the content of the file sequentially
 * @param file_input the file name
 * @return the string that represents the loaded file inside the memory
 */
std::string seq_read_file(const std::string &file_input);

#endif //SPM_PROJECT_SEQ_READ_HPP
