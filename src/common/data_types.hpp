//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_DATA_TYPES_HPP
#define SPM_PROJECT_DATA_TYPES_HPP

#include "array"
#include "string"

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
 * @brief Here I define for simplicity a new type for HuffMap.
 */
struct HuffMap : public std::array<std::string, 256> {};

#endif //SPM_PROJECT_DATA_TYPES_HPP
