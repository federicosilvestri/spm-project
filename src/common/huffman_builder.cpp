//
// Created by federicosilvestri on 13/10/23.
//

#include "huffman_map.hpp"
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
        unsigned char key = i;
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

void encode_tree(HuffNode *node, HuffCode partial_node, HuffMap &map) {
    // DFS Recursive algorithm

    if (node == nullptr) {
        // we reached the end of the tree
        return;
    }

    if (node->is_leaf()) {
        map[node->get_char()] = partial_node;
    }

    // go to left
    encode_tree(node->get_left(), partial_node.add(false), map);
    // go to right
    encode_tree(node->get_left(), partial_node.add(true), map);
}

HuffMap build_huffman_map(HuffNode *tree) {
    HuffMap huff_map;
    HuffCode huff_code;

    encode_tree(tree, huff_code, huff_map);
    return huff_map;
}