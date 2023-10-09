cmake_minimum_required(VERSION 3.0)
project(spm_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(spm_project
        src/main.cpp
        src/seq/seq_impl.cpp
        src/seq/seq_impl.hpp
        src/seq/stages/frequency_mapper.cpp
        src/seq/stages/frequency_mapper.h
)
