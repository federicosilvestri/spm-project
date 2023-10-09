cmake_minimum_required(VERSION 3.0)
project(spm_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(spm_project
        src/main.cpp
        src/seq/seq_impl.cpp
        src/seq/seq_impl.hpp
        src/seq/stages/seq_freq_map.cpp
        src/seq/stages/seq_freq_map.h
        src/utils/file_utils.cpp
        src/thr/thr_impl.cpp
        src/thr/thr_impl.hpp
        src/thr/stages/thr_freq_map.cpp
        src/thr/stages/thr_freq_map.hpp
)
