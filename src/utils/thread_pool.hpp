//
// Created by federicosilvestri on 03/09/23.
//

#ifndef SPM_PROJECT_THREAD_POOL_HPP
#define SPM_PROJECT_THREAD_POOL_HPP

#include <utility>
#include <queue>
#include <functional>
#include <thread>
#include <condition_variable>
#include <type_traits>
#include <mutex>
#include <exception>
#include <future>
#include <memory>

using namespace std;


/**
 * @brief My second implementation of a Synchronized Thread Pool with a simple Task Queue.
 * The name Super is just for fun, sorry about this.
 */
class [[nodiscard]] SuperThreadPool {
public:

    explicit SuperThreadPool(unsigned int n_worker) : pool(make_unique<vector<thread>>(n_worker)) {
        start_workers();
    }

    unsigned int get_nw() {
        return pool->size();
    }

    /**
     * @brief Push a task (without arguments) inside the queue.
     *
     * @param task The function to be executed.
     */
    template<typename T>
    void submit(T &&task) {
        task_queue_mtx.lock();
        task_queue.push(forward<T>(task));
        task_queue_mtx.unlock();
        new_task_cond_v.notify_one();
    }


    /**
     * @brief Wait for all tasks to be completed.
     */
    void wait_all();


    ~SuperThreadPool() {
        // Wait that pool finishes the work
        wait_all();
        // Destroy all threads
        stop_workers();
    }

private:
    /**
     * @brief Create the threads in the pool and assign a worker to each thread.
     */
    void start_workers();

    /**
     * @brief Destroy the threads in the pool.
     */
    void stop_workers();


    /**
     * @brief A worker function to be assigned to each thread in the pool. Waits until it is notified by submit() that a task is available, and then retrieves the task from the queue and executes it. Once the task finishes, the worker notifies wait_all() in case it is waiting.
     */
    void worker();

    /*
     * - - - TASKS QUEUE DEFINITIONS  - - -
     */
    /**
    * @brief MAIN queue for tasks.
    */
    queue<function<void()>> task_queue = {};
    /**
     * @brief Mutex for synchronize the access to the queue.
     */
    mutable mutex task_queue_mtx = {};


    /*
     * - - - THREAD POOL DEFINITIONS  - - -
     */
    /**
     * @brief Unique pointer for pool of runner (vector of threads).
     */
    unique_ptr<std::vector<std::thread>> pool = nullptr;
    /**
     * @brief Condition variable for notifying that a new task is available.
     */
    condition_variable new_task_cond_v = {};

    /**
     * @brief Condition variable for wait function (called by user) that becomes available when all tasks are done.
     */
    condition_variable task_executed_cond_v = {};

    /*
     * - - - UTILITY DEFINITIONS  - - -
     */
    /**
     * @brief A counter for the total number of currently running tasks.
     */
    unsigned int tasks_in_running = 0;
    /**
     * @brief Boolean var to indicate that someone is waiting for the task to be completed.
     */
    bool wait_active = false;
    /**
     * @brief Variable that indicate when the pool must stop. (CAUTION).
     */
    bool pool_running = false;
};

#endif //SPM_PROJECT_THREAD_POOL_HPP