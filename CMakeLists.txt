cmake_minimum_required(VERSION 3.5)
project(spm_project)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -fsanitize=thread -fstack-check -fstack-protector-strong -fno-omit-frame-pointer")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(spm_project
        src/main.cpp
        src/seq/seq_impl.cpp
        src/seq/seq_impl.hpp
        src/seq/stages/seq_freq_map.cpp
        src/seq/stages/seq_freq_map.h
        src/thr/thr_impl.cpp
        src/thr/thr_impl.hpp
        src/thr/stages/thr_freq_map.cpp
        src/thr/stages/thr_freq_map.hpp
        src/test/test_common.h
        src/test/test.cpp
        src/utils/logger.cpp
        src/utils/logger.hpp
        src/common/huffman_tree.cpp
        src/common/huffman_tree.hpp
        src/common/huffman_builder.cpp
        src/common/huffman_map.hpp
        src/seq/stages/seq_mapping.cpp
        src/seq/stages/seq_mapping.hpp
        src/common/file_writer.cpp
        src/common/file_writer.hpp
        src/utils/my_timer.cpp
        src/utils/my_timer.hpp
        src/common/frequency.hpp
        src/thr/stages/thr_mapping.cpp
        src/thr/stages/thr_mapping.hpp
        src/seq/stages/seq_transform.cpp
        src/seq/stages/seq_transform.hpp
)
