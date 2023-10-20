//
// Created by federicosilvestri on 20/10/23.
//

#ifndef SPM_PROJECT_THREAD_POOL_HPP
#define SPM_PROJECT_THREAD_POOL_HPP
#include "thread"
#include "condition_variable"
#include "mutex"
#include "functional"
#include "queue"

using namespace std;

/**
 * @brief Here I define a simple ThreadPool that (should be) used instead of creating threads each time.
 * It should be initialised at the beginning of parallel code.
 * I developed it during the study of first 7 lessons of SPM and now I try to reuse it to minimize the overheads.
 */

class ThreadPool {
    /*
     * - - - - Public sections - - - -
     */
public:
    /**
     * @brief Create the pool with p_degree parallelism, that is the number of workers inside the the queue.
     * @param p_degree Number of workers. If 0 it is set automatically to the maximum.
     */
    ThreadPool(const unsigned int p_degree);

    /**
     * @brief A constructor that is able to wait the threads before deleting them.
     */
    ~ThreadPool();

    /**
     * @brief Get the number of threads used. If you have set the p_degree to 0, it will return the number of ma
     * maximum thread.
     * @return Unsigned int that represents the real number of workers.
     */
    unsigned int get_p_degree();

    void wait_tasks();

private:
    // The parallelism degree
    unsigned int p_degree;

    // Condition variable to notify the thread that a new TASK is available.
    condition_variable task_available_v = {};

    // Condition variable to notify that a thread has finished the TASK
    condition_variable task_done_v = {};

    // Task queue
    queue<function<void()>> task_queue = {};

    // Mutex for queue sync
    mutex tasks_queue_mtx;

    // Variable to store the number of running TASKS
    unsigned int task_in_running;

    // Container for threads
    vector<thread> threads;

    // Is the ThreadPool waiting for task to be finished?
    bool waiting = false;

    // Variable that maintains the threads alive, when it is set to false, threads will die
    bool running = false;

    // create the internal pool
    void create_pool();

    // destruct pool
    void destruct_pool();

    // The function that represents the worker
    void worker();

};

#endif //SPM_PROJECT_THREAD_POOL_HPP
