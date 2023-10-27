//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_DATA_TYPES_HPP
#define SPM_PROJECT_DATA_TYPES_HPP
#include "array"
#include "string"

// Defining the alphabet len, ASCII is 256
#define ALPHABET_LEN 256

/**
 * @brief Definition of Frequency Map as a static fixed size array.
 */
struct FrequencyMap : public std::array<unsigned int, ALPHABET_LEN> {
    /*
     * Overload the constructor to fill entire array to 0.
     */
    FrequencyMap() : array() {
        this->fill(0);
    }
};

/**
 * @brief Here I define for simplicity a new type for HuffMap.
 */
struct HuffMap : public std::array<std::string, ALPHABET_LEN> {};


#endif //SPM_PROJECT_DATA_TYPES_HPP
