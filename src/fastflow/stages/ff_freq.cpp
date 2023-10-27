//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_freq.hpp"
#include "string"
#include "ff/parallel_for.hpp"
#include "ff/node.hpp"
#include "ff/ff.hpp"
#include "../../common/data_types.hpp"

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

typedef struct task {
    const string &file_content;
    FrequencyMap *f_map;
    unsigned int nw;
    unsigned long start;
    unsigned long stop;

    explicit task(const string &f_c) : file_content(f_c), f_map(new FrequencyMap()) {}

} FREQ_TASK;

class CharacterEmitter : public ff_monode_t<FREQ_TASK> {

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

    CharacterEmitter(const string &file_content, unsigned int nw) : file_content(file_content), nw(nw) {}

    FREQ_TASK *svc(FREQ_TASK *) override {
        unsigned long chunk_size = FREQ_CHUNK_SIZE(file_content.size(), nw);
        for (unsigned long i = 0; i < file_content.size(); i += chunk_size) {
            auto task = new FREQ_TASK(file_content);
            task->start = i;
            task->stop = min(i + chunk_size, file_content.size());
            task->nw = nw;
            ff_send_out(task);
        }
        return EOS;
    }
};

class FrequencyMapWorker : public ff_node_t<FREQ_TASK> {
public:
    FREQ_TASK *svc(FREQ_TASK *task) override {
        for (unsigned long i = task->start; i < task->stop; i++) {
            auto c = static_cast<unsigned char>(task->file_content[i]);
            (*task->f_map)[c] += 1;
        }
        return task;
    }


};


class FrequencyMapCollector : public ff_node_t<FREQ_TASK> {
public:
    FREQ_TASK *svc(FREQ_TASK *task) override {
        free(task);
        return GO_ON;
    }


};


FrequencyMap ff_compute_frequencies(const std::string &content, unsigned int p_degree) {
    /*
     * Using a static strategy, because the work is equally complexed.
     */

    vector<unique_ptr<ff_node>> workers(p_degree);
    for (int i = 0; i < p_degree; i++) {
        workers[i] = make_unique<FrequencyMapWorker>();
    }
    auto emitter = CharacterEmitter(content, p_degree);
    auto collector = FrequencyMapCollector();

    ff_Farm<> farm(std::move(workers), emitter, collector);
    farm.run_and_wait_end();

}