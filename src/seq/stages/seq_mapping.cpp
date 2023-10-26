//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "vector"
#include "seq_mapping.hpp"

using namespace std;

OutputBuffer seq_mapping(HuffMap &huff_map, const string &file_content) {
    /*
     * Maps the content of the file into a binary code.
     */

    // compute the size
    auto final_size = compute_huffman_size(huff_map);
    final_size = (final_size / 8) + (final_size % 8 != 0);

    // Output buffer
    OutputBuffer ob(1);
    ob.buffer[0] = vector<unsigned char>(final_size);
    ob.chunk_info[0] = final_size;

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
    // Current index
    unsigned int current_index = 0;

    for (auto i = 0L; i < file_content.size(); i++) {
        unsigned char read_char = file_content[i];
        HuffCode hc = huff_map.at(read_char);
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
            ob.buffer[0][current_index++] = buff;
            buff = 0;
            w_size = 0;
        }

        if (bits_to_write) {
            buff |= (hc.code << bits_written);
            w_size += bits_to_write;
            bits_to_write = 0;
            pending_bits = true;
        }

        if (i == (file_content.size() - 1) && pending_bits) {
            ob.buffer[0][current_index++] = buff;
        }

    }

    return ob;
}