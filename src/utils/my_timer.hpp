//
// Created by federicosilvestri on 16/10/23.
//

#ifndef SPM_PROJECT_MY_TIMER_HPP
#define SPM_PROJECT_MY_TIMER_HPP

#include "string"
#include "chrono"
#include "vector"

/**
 * @brief Simple class to collect and measure the time between two invocations of stop and start.
 */
class MyTimer {
private:
    std::string last_time_name;
    std::chrono::high_resolution_clock::time_point last_start;
    std::vector<std::pair<std::string, std::chrono::high_resolution_clock::duration>> timings;
public:
    /**
     * @brief Create a new Timer object.
     */

    /**
     * @brief Start the timer.
     * @param time_name the name of the measure
     */
    void start(const std::string &time_name);

    /**
     * @brief Stop the timer. It will push back the results into internal store.
     */
    void stop();

    /**
     * @brief Print the timings (with specific syntax).
     */
    void print_timings();
};


#endif //SPM_PROJECT_MY_TIMER_HPP
