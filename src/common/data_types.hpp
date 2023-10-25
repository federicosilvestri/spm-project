//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_DATA_TYPES_HPP
#define SPM_PROJECT_DATA_TYPES_HPP

#include "array"
#include "string"
#include "stdexcept"
#include "unordered_map"
#include "iostream"

/**
 * @brief Definition of Frequency Map as a static fixed size array.
 */
struct FrequencyMap : public std::array<unsigned int, 256> {
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
     * @brief The size of the code (it must be always <=8.
     */
    unsigned int size;

    HuffCode() {
        code = 0;
        size = 0;
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

#endif //SPM_PROJECT_DATA_TYPES_HPP
