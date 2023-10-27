//
// Created by federicosilvestri on 03/09/23.
//
#include "thread_pool.hpp"

void SuperThreadPool::wait_all() {
    unique_lock tasks_lock(task_queue_mtx);
    wait_active = true;
    task_executed_cond_v.wait(tasks_lock, [this] { return !tasks_in_running && task_queue.empty(); });
    wait_active = false;
}

void SuperThreadPool::start_workers() {
    task_queue_mtx.lock();
    pool_running = true;
    task_queue_mtx.unlock();

    for (unsigned int i = 0; i < pool->size(); ++i) {
        (*pool)[i] = thread(&SuperThreadPool::worker, this);
    }

}

void SuperThreadPool::stop_workers() {
    task_queue_mtx.lock();
    pool_running = false;
    task_queue_mtx.unlock();

    new_task_cond_v.notify_all();
    for (unsigned int i = 0; i < pool->size(); ++i) {
        (*pool)[i].join();
    }
}

void SuperThreadPool::worker() {
    function<void()> task;
    while (true) {
        /*
         * Fetching the task from the queue.
         */
        unique_lock tasks_lock(task_queue_mtx);
        new_task_cond_v.wait(tasks_lock, [this] { return !task_queue.empty() || !pool_running; });
        if (!pool_running) {
            // Thread pool is closed. We can stop to work.
            break;
        }
        // get the task
        task = std::move(task_queue.front());
        task_queue.pop();
        tasks_in_running += 1;
        tasks_lock.unlock();

        // Execute the task.
        task();

        // locking again to tell that task if finished
        tasks_lock.lock();
        tasks_in_running -= 1;
        if (wait_active && !tasks_in_running && task_queue.empty())
            // if someone is waiting for task AND there are no tasks in running state AND the queue is empty
            // we can notify the user that all tasks are done.
            task_executed_cond_v.notify_all();
    }
}