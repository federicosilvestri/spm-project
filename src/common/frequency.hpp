//
// Created by federicosilvestri on 16/10/23.
//

#ifndef SPM_PROJECT_FREQUENCY_HPP
#define SPM_PROJECT_FREQUENCY_HPP
#include "unordered_map"
#include "vector"

/**
 * @brief FrequencyMap type.
 */
 typedef std::unordered_map<char, unsigned int> FrequencyMap;

/**
 * @brief Vector of frequencies.
 */
 typedef std::vector<FrequencyMap> FrequencyVector;

#endif //SPM_PROJECT_FREQUENCY_HPP
