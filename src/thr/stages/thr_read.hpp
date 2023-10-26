//
// Created by federicosilvestri on 19/10/23.
//

#ifndef SPM_PROJECT_THR_READ_HPP
#define SPM_PROJECT_THR_READ_HPP
#include "string"
#include "../../utils/thread_pool.hpp"


std::string thr_read_file(const std::string& input_file, SuperThreadPool& thread_pool);

#endif //SPM_PROJECT_THR_READ_HPP
