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
    bool pending_bits;

    for (auto i = start; i <= end; i++) {
        unsigned char read_char = file_content[i];
        HuffCode hc = huff_map.at(read_char);
        total_write += hc.size;
        pending_bits = false;

        if (w_size + hc.size <= 8) {
            buff |= (hc.code >> w_size);
            w_size += hc.size;
        } else if (w_size + hc.size > 8) {
            bits_written = 8 - w_size;
            bits_to_write = hc.size - bits_written;
            buff |= (hc.code >> w_size);
            w_size = 8;
        }

        if (w_size == 8) {
            out_buff.buffer[buff_index].push_back(buff);
            buff = 0;
            w_size = 0;
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


OutputBuffer thr_mapping(HuffMap &huff_map, const string &file_content, unsigned int p_degree) {
    /*
     * I split again the file into chunks, and I assign statically a chunk of data
     * to a thread. The task for each thread is equally complex and the effort of each thread is balanced.
     */
    unsigned int f_size = file_content.size();
    // adjusting the parallelism, computing chunk size or delta, is the same.
    unsigned int chunk_size = (f_size / p_degree) + (f_size % p_degree != 0);
    if (p_degree > f_size) {
        // chunk_size < 1
        // at least 1 character per thread...
        p_degree = f_size;
    }

    // a vector of threads.
    vector<thread> workers(p_degree);
    // the local mapped vector.
    OutputBuffer of(p_degree);

    for (auto i = 0; i < p_degree; i++) {
        auto start = i * chunk_size;
        auto end = min(start + chunk_size - 1, f_size - 1);

        auto pFunction = [&of, i, start, end, &file_content, &huff_map]() {
            mapper_worker(huff_map, file_content, start, end, i, of);
        };

        workers[i] = thread(pFunction);
    }


    for (auto i = 0; i < workers.size(); i++) {
        // waiting for threads
        workers[i].join();
    }

    for (auto &p: of.chunk_info) {
        cout << "SIZE=" << p << endl;
    }

    return of;
}