#
# My CMake file
#
cmake_minimum_required(VERSION 3.5)
project(
        spm_project
        VERSION 1.0
        DESCRIPTION "Final Project for SPM, Parallel Huffman Encoding"
        LANGUAGES CXX
)

# Setting global options.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(THREADS_PREFER_PTHREAD_FLAG ON)
OPTION(FF_DISABLE "Option description" OFF) # Disabled by default

# Set the options for debug target
#set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -fsanitize=thread -fstack-check -fstack-protector-strong -fno-omit-frame-pointer")

# Set the options for release target
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fsanitize=thread -fstack-check -ftree-vectorize")

# set(CMAKE_CXX_FLAGS "-O3")

# Add files
if (FF_DISABLE)
    add_definitions(-DFF_DISABLE)
    message("Fastflow DISABLED")

    add_executable(spm_project
            src/main.cpp
            src/seq/seq_impl.cpp
            src/seq/seq_impl.hpp
            src/seq/stages/seq_freq.cpp
            src/seq/stages/seq_freq.h
            src/thr/thr_impl.cpp
            src/thr/thr_impl.hpp
            src/thr/stages/thr_freq.cpp
            src/thr/stages/thr_freq.hpp
#            src/test/test_common.h
#            src/test/test.cpp
            src/utils/logger.cpp
            src/utils/logger.hpp
            src/common/huffman_tree.cpp
            src/common/huffman_tree.hpp
            src/common/huffman_builder.cpp
            src/common/huffman_map.hpp
            src/seq/stages/seq_mapping.cpp
            src/seq/stages/seq_mapping.hpp
            src/common/write.cpp
            src/common/write.hpp
            src/utils/my_timer.cpp
            src/utils/my_timer.hpp
            src/thr/stages/thr_mapping.cpp
            src/thr/stages/thr_mapping.hpp
            src/seq/stages/seq_transform.cpp
            src/seq/stages/seq_transform.hpp
            src/thr/stages/thr_transform.cpp
            src/thr/stages/thr_transform.hpp
            src/thr/stages/thr_read.cpp
            src/thr/stages/thr_read.hpp
            src/seq/stages/seq_read.hpp
            src/seq/stages/seq_read.cpp

    )
else ()
    message("Fastflow ENABLED")
    add_executable(spm_project
            src/main.cpp
            src/seq/seq_impl.cpp
            src/seq/seq_impl.hpp
            src/seq/stages/seq_freq.cpp
            src/seq/stages/seq_freq.h
            src/thr/thr_impl.cpp
            src/thr/thr_impl.hpp
            src/thr/stages/thr_freq.cpp
            src/thr/stages/thr_freq.hpp
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
            src/common/write.cpp
            src/common/write.hpp
            src/utils/my_timer.cpp
            src/utils/my_timer.hpp
            src/thr/stages/thr_mapping.cpp
            src/thr/stages/thr_mapping.hpp
            src/seq/stages/seq_transform.cpp
            src/seq/stages/seq_transform.hpp
            src/thr/stages/thr_transform.cpp
            src/thr/stages/thr_transform.hpp
            src/thr/stages/thr_read.cpp
            src/thr/stages/thr_read.hpp
            src/seq/stages/seq_read.hpp
            src/seq/stages/seq_read.cpp
            src/fastflow/ff_impl.cpp
            src/fastflow/ff_impl.hpp
            src/fastflow/stages/ff_freq.hpp
            src/fastflow/stages/ff_freq.cpp
            src/fastflow/stages/ff_mapping.cpp
            src/fastflow/stages/ff_mapping.hpp
            src/fastflow/stages/ff_transform.cpp
            src/fastflow/stages/ff_transform.hpp
    )
endif ()