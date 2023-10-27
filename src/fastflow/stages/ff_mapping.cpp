//
// Created by federicosilvestri on 20/10/23.
//

#include "ff_mapping.hpp"
#include "ff/ff.hpp"
#include "ff/node.hpp"

#define MAPPER_CHUNK_SIZE(size, p) ((size / p) + (size % p != 0))
using namespace std;
using namespace ff;

/**
 * Farm emitter.
 */
class MapperEmitter : public ff_monode_t<MapperWorkerTask> {

private:
    /**
     * @brief The file file content
     */
    const string &file_content;

    /**
     * @briefNumber of workers
     */
    const unsigned int nw;

public:

    /**
     * Create a new emitter. It emits a Mapper Task.
     * @param file_content constant file content
     * @param nw number of worker (necessary)
     */
    MapperEmitter(const string &file_content, const unsigned int nw)
            : file_content(file_content), nw(nw) {}

    /**
     * Service node.
     * @return The task to be executed by workers.
     */
    MapperWorkerTask *svc(MapperWorkerTask *) override {
        unsigned long chunk_size = MAPPER_CHUNK_SIZE(file_content.size(), nw);
        unsigned int buff_index = 0;
        for (unsigned long i = 0; i < file_content.size(); i += chunk_size) {
            auto task = new MapperWorkerTask(i, min(i + chunk_size, file_content.size()), buff_index);
            ff_send_out(task);
            buff_index += 1;
        }
        return EOS;
    }
};

/**
 * @brief Mapper Worker Node
 */
class MapperWorker : public ff_node_t<MapperWorkerTask> {

private:
    /**
     * @brief The file content
     */
    const string &file_content;

    /**
     * @brief The HuffMap
     */
    const HuffMap &huff_map;

    /**
     * @brief The OutputBuffer
     */
    OutputBuffer *output_buffer;


public:
    explicit MapperWorker(const string &fileContent, const HuffMap &huffMap, OutputBuffer *outputBuffer)
            : file_content(fileContent), huff_map(huffMap), output_buffer(outputBuffer) {}


    MapperWorkerTask *svc(MapperWorkerTask *task) override {
        /*
         * Maps the content of the file into a binary code.
         *
         */

        // Total bits written
        uint64_t total_write;
        // Current Buffer
        unsigned char buff = 0;
        // Window size
        unsigned int w_size = 0;
        // Bits that does not fit inside the current buffer and must be written in the next buffer.
        unsigned int bits_to_write = 0;
        // Bits available that can be written inside the buffer.
        unsigned int bits_written;
        // Variable to monitor if there are bits pending to be pushed
        bool pending_bits = false;

        for (auto i = task->start; i < task->stop; i++) {
            unsigned char read_char = file_content[i];
            HuffCode hc = huff_map.at(read_char);
            total_write += hc.size;

            if (w_size + hc.size <= WINDOW_SIZE) {
                buff |= (hc.code >> w_size);
                w_size += hc.size;
                pending_bits = true;
            } else if (w_size + hc.size > WINDOW_SIZE) {
                bits_written = WINDOW_SIZE - w_size;
                bits_to_write = hc.size - bits_written;
                buff |= (hc.code >> w_size);
                w_size = WINDOW_SIZE;
            }

            if (w_size == WINDOW_SIZE) {
                output_buffer->buffer[task->buff_index].push_back(buff);
                buff = 0;
                w_size = 0;
                pending_bits = false;
            }

            if (bits_to_write) {
                buff |= (hc.code << bits_written);
                w_size += bits_to_write;
                bits_to_write = 0;
                pending_bits = true;
            }

            if (i == task->stop - 1 && pending_bits) {
                output_buffer->buffer[task->buff_index].push_back(buff);
            }
        }

        output_buffer->chunk_info[task->buff_index] = total_write;
    }
};

OutputBuffer ff_mapping(HuffMap &huff_map, const string &file_content, unsigned int p_degree) {
    auto out_buff = new OutputBuffer(p_degree);

    auto emitter = MapperEmitter(file_content, p_degree);
    return *out_buff;
}