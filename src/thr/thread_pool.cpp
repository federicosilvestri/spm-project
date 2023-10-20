//
// Created by federicosilvestri on 20/10/23.
//

#include "thread_pool.hpp"

ThreadPool::ThreadPool(const unsigned int p_degree) {
    this->p_degree = p_degree == 0 ? thread::hardware_concurrency() : p_degree;
    create_pool();
}

unsigned int ThreadPool::get_p_degree() {
    return this->p_degree;
}

ThreadPool::~ThreadPool() {
    // wait threads (TODO)
    // destroy it
    this->destruct_pool();

}

void ThreadPool::create_pool() {
    // lock the access to queue
    this->tasks_queue_mtx.lock();
    this->running = true;
    for (int i = 0; i < this->p_degree; i++) {
        threads.emplace_back(thread(&ThreadPool::worker, this));
    }
    this->tasks_queue_mtx.unlock();
}

void ThreadPool::worker() {
    // declare the task to be done
    function<void()> my_task;
    while (true) {
        /*
         *
         * ! ! ! CIRITICAL SECTION ! ! !
         *
         */
        unique_lock w_lock(tasks_queue_mtx);
        task_available_v.wait(w_lock, [this]() {
            // if the queue is not empty or the queue is poisoned.
            return !task_queue.empty() || !running;
        });

        if (!running) {
            // queue is poisoned, we need to stop.
            break;
        }

        task_in_running += 1;
        // get the task from the queue and remove it
        my_task = move(task_queue.front());
        task_queue.pop();
        // unlock the queue
        w_lock.unlock();

        // execute the task
        my_task();

        // Critical section, again!
        w_lock.lock();
        task_in_running -= 1;
        if (waiting && !task_in_running && task_queue.empty()) {
            // if we are waiting for task or there are other task in running or the queue is empty
            task_done_v.notify_all();
        }
    }
}

void ThreadPool::destruct_pool() {
    this->tasks_queue_mtx.lock();
    this->running = false;
    this->tasks_queue_mtx.unlock();

    // notify all the threads for a new job! (poisoning)
    task_available_v.notify_all();
    // waiting the threads for finish
    for (auto &t: this->threads) {
        t.join();
    }
    // done!
}

void ThreadPool::wait_tasks() {
    unique_lock w_lock(tasks_queue_mtx);
    waiting = true;
    task_done_v.wait(
            w_lock,
            [this]() { return !task_in_running && task_queue.empty(); }
    );
    waiting = false;
}
