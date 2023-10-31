//
// Created by federicosilvestri on 13/10/23.
//
#include <cstdint>
#include "stdexcept"
#include "seq_mapping.hpp"

using namespace std;

OutputBuffer seq_mapping(HuffMap &huff_map, const string &file_content) {
    /*
     * Maps the content of the file into a binary code.
     */

    // Output buffer
    OutputBuffer ob(1);
    // Total bits written
    uint64_t total_write = 0;
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

    for (auto i = 0L; i < file_content.size(); i++) {
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
            ob.buffer[0].push_back(buff);
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

        if (i == (file_content.size() - 1) && pending_bits) {
            ob.buffer[0].push_back(buff);
        }

    }

    // setting the chunk size info
    ob.chunk_info[0] = total_write;

    return ob;
}