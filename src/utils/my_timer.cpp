//
// Created by federicosilvestri on 16/10/23.
//

#include "my_timer.hpp"
#include "iostream"

void MyTimer::start(const std::string &time_name) {
    MyTimer::last_time_name = time_name;
    MyTimer::last_start = std::chrono::high_resolution_clock::now();
}

void MyTimer::stop() {
    auto duration = std::chrono::high_resolution_clock::now() - MyTimer::last_start;
    MyTimer::timings.emplace_back(MyTimer::last_time_name, duration);
}

void MyTimer::print_timings() {
    long total = 0;
    for (auto &measure: MyTimer::timings) {
        auto time = measure.second.count();
        std::cout << measure.first << "=" << time << "ns" << std::endl;
        total += time;
    }
    std::cout << "TOTAL=" << total << "ns" << std::endl;
}
