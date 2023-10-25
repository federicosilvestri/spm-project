//
// Created by federicosilvestri on 13/10/23.
//

#include "huffman_builder.hpp"
#include "vector"
#include "queue"

using namespace std;

HuffNode *build_huffman_tree(FrequencyMap &f_map) {
    /* The algorithm from literature suggests to use a priority queue
     * where the priority is defined by probability (i.e. frequency).
     * Here I define as container for the queue a vector of HuffNode,
     * that already implements the operations of comparison based on frequency.
     */
    priority_queue<HuffNode *, vector<HuffNode *>, CompareHuffNodes> queue;

    // first step: push all data inside the queue.
    for (int i = 0; i < f_map.size(); i++) {
        auto key = static_cast<unsigned char>(i);
        unsigned int freq = f_map[i];

        if (f_map[i] > 0) {
            queue.push(new HuffNode(key, freq));
        }
    }

    // second step: iterates until the queue > 1
    while (queue.size() > 1) {
        auto left = queue.top();
        queue.pop();
        auto right = queue.top();
        queue.pop();

        auto freq_sum = left->get_freq() + right->get_freq();
        auto up = new HuffNode(HUFF_ESCAPE_CHAR, freq_sum, left, right, false);
        queue.push(up);
    }

    HuffNode *tree = queue.top();
    queue.pop();
    return tree;
}

void dfs_visit(HuffNode *node, HuffCode partial_node, HuffMap &map) {
    // DFS Recursive algorithm
    if (node->is_leaf()) {
        partial_node.frequency = node->get_freq();
        map.insert({node->get_char(), partial_node});
    }

    if (node->get_left() != nullptr) {
        // go to left
        dfs_visit(node->get_left(), partial_node.add(false), map);
    }
    if (node->get_right() != nullptr) {
        // go to right
        dfs_visit(node->get_right(), partial_node.add(true), map);
    }
}

HuffMap build_huffman_map(HuffNode *tree) {
    HuffMap huff_map;
    HuffCode huff_code;

    dfs_visit(tree, huff_code, huff_map);
    return huff_map;
}

unsigned long compute_huffman_size(HuffMap &huff_map) {
    /*
     * For each element in the map sum the product of frequency and size :)
     */
    unsigned long compressed_size = 0L;
    for (auto &p: huff_map) {
        compressed_size += p.second.frequency * p.second.size;
    }

    return compressed_size;
}