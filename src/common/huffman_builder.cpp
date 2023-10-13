//
// Created by federicosilvestri on 13/10/23.
//

#include "huffman_builder.hpp"
#include "vector"
#include "queue"
#include "iostream"

using namespace std;

HuffNode *build_huffman_tree(unordered_map<char, unsigned int> &data_map) {
    /* The algorithm from literature suggests to use a priority queue
     * where the priority is defined by probability (i.e. frequency).
     * Here I define as container for the queue a vector of HuffNode,
     * that already implements the operations of comparison based on frequency.
     */
    priority_queue<HuffNode *, vector<HuffNode *>, CompareHuffNodes> queue;

    // first step: push all data inside the queue.
    for (auto &pair: data_map) {
        queue.push(new HuffNode(
                pair.first,
                pair.second
        ));
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

void encode_tree(HuffNode *node, string partial_enc, unordered_map<char, string> &map) {
    // DFS Recursive algorithm

    if (node == nullptr) {
        // we reached the end of the tree
        return;
    }

    if (node->is_leaf()) {
        map.insert({node->get_char(), partial_enc});
    }

    // go to left
    encode_tree(node->get_left(), partial_enc + "0", map);
    // go to right
    encode_tree(node->get_right(), partial_enc + "1", map);
}

unordered_map<char, string> build_huffman_map(HuffNode *tree) {
    unordered_map<char, string> huff_map;
    string encoded_string;

    encode_tree(tree, encoded_string, huff_map);
    return huff_map;
}