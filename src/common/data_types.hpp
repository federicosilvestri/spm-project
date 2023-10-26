//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_DATA_TYPES_HPP
#define SPM_PROJECT_DATA_TYPES_HPP
#pragma once

#include "array"
#include "string"
#include "stdexcept"
#include "unordered_map"
#include "vector"
#include "iostream"
#include "utility"


/**
 * @brief Definition of Frequency Map as a static fixed size array.
 */
struct FrequencyMap : public std::array<unsigned long, 256> {
    /*
     * Overload the constructor to fill entire array to 0.
     */
    FrequencyMap() : array() {
        this->fill(0);
    }
};

/**
 * @brief Representation of HuffCode. It is pair of a byte and a size, where byte represent the payload of Huffman code
 * and the size represents how many bit are significant, starting from left to right.
 */
struct HuffCode {
    /**
     * @brief The represented code in binary.
     */
    unsigned char code;
    /**
     * @brief The size of the code (it must be always <=8).
     */
    unsigned int size;

    /**
     * @brief Associated frequency for this code (Needed for PRE-computing the space)
     */
     unsigned long frequency;

    HuffCode() {
        code = 0;
        size = 0;
        frequency = 0L;
    }

    [[nodiscard]] HuffCode add(bool right) const {
        if (size == 8) {
            throw std::invalid_argument("Overflow of Huffcode");
        }
        HuffCode c = HuffCode();
        // copy node date into new
        c.code = code;

        // increase the size
        c.size = size + 1;

        if (right) {
            // set the most significant bit to 1
            c.code |= (1 << (8 - c.size));
        }
        return c;
    }

};

/**
 * @brief Here I define for simplicity a new type for HuffMap.
 */
typedef std::unordered_map<unsigned char, HuffCode> HuffMap;

/**
 * @brief The size of window for output buffer
 */
typedef u_int32_t WINDOW_TYPE;

/**
 * @brief The size of the window (in bits).
 */
const size_t WINDOW_SIZE = sizeof(WINDOW_TYPE) * 8;

/**
 * @brief Here I defined a struct for containing the compressed data, including metadata info.
 */
struct OutputBuffer {

    /**
     * @brief The metadata as a list of unsigned long (4Bytes) that represents the X significant bits of the chunk.
     * If X is not a multiple of 8, it means that X + (X % 8)bits are padding bits.
     * Here I use a fixed width integer type that is uint_64 (8byte). It means that for each chunk I can
     * index at most 2^64 bit, hence a very big chunk..
     */
    std::vector<u_int64_t> chunk_info;

    /**
     * @brief The payload.
     */
    std::vector<std::vector<WINDOW_TYPE>> buffer;


    /**
     * @brief To rebuild the file the decompressor needs the HuffMan tree. Here is omitted for simplicity of serializing
     * the structure.
     * huffman_tree
     */

    explicit OutputBuffer(unsigned int size) {
        buffer = std::vector<std::vector<WINDOW_TYPE>>(size);
        chunk_info = std::vector<u_int64_t>(size);
    }

};

#endif //SPM_PROJECT_DATA_TYPES_HPP
