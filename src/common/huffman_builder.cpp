//
// Created by federicosilvestri on 13/10/23.
//

#include "huffman_map.hpp"
#include "vector"
#include "queue"

using namespace std;

HuffNode *build_huffman_tree(vector<unsigned int> &data_map) {
    /* The algorithm from literature suggests to use a priority queue
     * where the priority is defined by probability (i.e. frequency).
     * Here I define as container for the queue a vector of HuffNode,
     * that already implements the operations of comparison based on frequency.
     */
    priority_queue<HuffNode *, vector<HuffNode *>, CompareHuffNodes> queue;

    // first step: push all data inside the queue.
    for (int i = 0; i < data_map.size(); i++) {
        char key = i;
        unsigned int freq = data_map[i];

        if (data_map[i] > 0) {
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

void encode_tree(HuffNode *node, string partial_enc, unordered_map<char, string> &map) {
    // DFS Recursive algorithm
    // TODO si può parallelizzare, mettendo la map con lock e facendo l'algoritmo non ricorsivo

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

HuffMap build_huffman_map(HuffNode *tree) {
    HuffMap huff_map;
    string encoded_string;

    encode_tree(tree, encoded_string, huff_map);
    return huff_map;
}