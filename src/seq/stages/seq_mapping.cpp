//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "vector"
#include "seq_mapping.hpp"

using namespace std;

unsigned long compute_compressed_size(HuffMap &huff_map, const string &file_content) {
    unsigned long size = 0L;

    for (unsigned char c: file_content) {
        HuffCode hc = huff_map.at(c);
        size += hc.size;
    }

    return size;
}


string seq_mapping(HuffMap &huff_map, const string &file_content) {
    /*
     * Maps the content of the file into a binary code.
     */
    auto size = compute_compressed_size(huff_map, file_content);

    unsigned int current_index = 0;
    // Final stream of encoded chars.
    vector<unsigned char> encoded(size);
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

    for (auto i = 0; i < file_content.size(); i++) {
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
            encoded[current_index++] = buff;
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
            encoded[current_index++] = buff;
        }

    }

    return string(encoded.cbegin(), encoded.cend());
}