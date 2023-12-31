//
// Created by federicosilvestri on 17/10/23.
//

#include "thr_mapping.hpp"
#include "thread"
#include "iostream"

using namespace std;

void mapper_worker(HuffMap &huff_map, const string &file_content, long start, long end, unsigned int buff_index,
                   OutputBuffer &out_buff) {
    /*
     * Maps the content of the file into a binary code.
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

    for (auto i = start; i <= end; i++) {
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
            out_buff.buffer[buff_index].push_back(buff);
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

        if (i == end - 1 && pending_bits) {
            out_buff.buffer[buff_index].push_back(buff);
        }
    }

    out_buff.chunk_info[buff_index] = total_write;

}


OutputBuffer thr_mapping(HuffMap &huff_map, const string &file_content, SuperThreadPool &tp) {
    /*
     * I split again the file into chunks, and I assign statically a chunk of data
     * to a thread. The task for each thread is equally complex and the effort of each thread is balanced.
     */
    auto p_degree = tp.get_nw();
    unsigned int f_size = file_content.size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // the local mapped vector.
    OutputBuffer of(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);

        auto pFunction = [&of, i, start, end, &file_content, &huff_map]() {
            mapper_worker(huff_map, file_content, start, end, i, of);
        };

        tp.submit(pFunction);
    }


    tp.wait_all();


    return of;
}