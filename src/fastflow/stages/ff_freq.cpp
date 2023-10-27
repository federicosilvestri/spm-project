//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_freq.hpp"
#include "ff/parallel_for.hpp"
#include "ff/node.hpp"
#include "ff/ff.hpp"

/*
 * Define the size of chunk that emitters has to emits.
 * If it is set to auto, it will be calculated as file_content.size() / nw
 */
#define FREQ_CHUNK_PURE false
#if FREQ_CHUNK_PURE
#define FREQ_CHUNK_SIZE(content_size, nw) 1
#else
#define FREQ_CHUNK_SIZE(content_size, nw) (content_size/nw + (content_size % nw != nw))
#endif

using namespace std;
using namespace ff;

/**
 * Farm emitter.
 */
class CharacterEmitter : public ff_monode_t<FrequencyWorkerTask> {

private:
    /**
     * @brief The file file content
     */
    const string &file_content;

    /**
     * @briefNumber of workers
     */
    unsigned int nw;

public:

    /**
     * Create a new emitter. It emits a Frequency Task.
     * @param file_content constant file content
     * @param nw number of worker (to compute eventually the chunk size)
     */
    CharacterEmitter(const string &file_content, unsigned int nw) : file_content(file_content), nw(nw) {}

    /**
     * Service node.
     * @return The task to be executed by workers.
     */
    FrequencyWorkerTask *svc(FrequencyWorkerTask *) override {
        unsigned long chunk_size = FREQ_CHUNK_SIZE(file_content.size(), nw);
        for (unsigned long i = 0; i < file_content.size(); i += chunk_size) {
            auto task = new FrequencyWorkerTask(file_content, i, min(i + chunk_size, file_content.size()));
            ff_send_out(task);
        }
        return EOS;
    }
};

/**
 * @brief Frequency Mapper Worker.
 */
class FrequencyMapWorker : public ff_node_t<FrequencyWorkerTask> {
public:
    /**
     * Service: compute the local frequencies
     * @param task the task that contains the work to be done
     * @return the task (to be sent to reducer)
     */
    FrequencyWorkerTask *svc(FrequencyWorkerTask *task) override {
        for (unsigned long i = task->start; i < task->stop; i++) {
            auto c = static_cast<unsigned char>(task->file_content[i]);
            (*task->f_map)[c] += 1;
        }
        return task;
    }


};

/**
 * @brief Collector of Farm. It receives the local maps and reduce it to a final map.
 */
class FrequencyMapCollector : public ff_node_t<FrequencyWorkerTask> {
private:
    /**
     * Final reduced map.
     */
    FrequencyMap *reduced;
public:

    FrequencyMapCollector() {
        reduced = new FrequencyMap();
    }

    /**
     * Service.
     * @param task The incoming task
     * @return FF GO_ON
     */
    FrequencyWorkerTask *svc(FrequencyWorkerTask *task) override {
        // Reduce the incoming local map to final (reduced)

        for (auto i = 0; i < reduced->size(); i++) {
            (*reduced)[i] += (*task->f_map)[i];
        }
        free(task);
        return GO_ON;
    }


    FrequencyMap *get_reduced_map() {
        return reduced;
    }

};


FrequencyMap ff_compute_frequencies(const std::string &content, unsigned int p_degree) {
    vector<unique_ptr<ff_node>> workers(p_degree);
    for (int i = 0; i < p_degree; i++) {
        workers[i] = make_unique<FrequencyMapWorker>();
    }
    auto emitter = CharacterEmitter(content, p_degree);
    auto collector = FrequencyMapCollector();

    ff_Farm<> farm(std::move(workers), emitter, collector);

    farm.run_and_wait_end();

    return *collector.get_reduced_map();

}