//
// Created by federicosilvestri on 13/10/23.
//
#include "stdexcept"
#include "huffman_tree.hpp"
#include "../utils/logger.hpp"

HuffNode::HuffNode(char character, unsigned int freq, HuffNode *left, HuffNode *right, bool leaf) {
    HuffNode::character = character;
    HuffNode::freq = freq;
    HuffNode::left = left;
    HuffNode::right = right;

    if (character != HUFF_ESCAPE_CHAR && !leaf) {
        throw std::invalid_argument("A non-leaf Nodes must contain ESCAPE_CHAR.");
    }

    HuffNode::leaf = leaf;
}

HuffNode::~HuffNode() {
    delete HuffNode::left;
    delete HuffNode::right;
}

unsigned int HuffNode::get_freq() {
    return HuffNode::freq;
}

char HuffNode::get_char() {
    if (!HuffNode::leaf) {
        throw std::invalid_argument("This node does not contain a character, it's defined as UP node.");
    }

    return HuffNode::character;
}

bool HuffNode::is_leaf() {
    return HuffNode::leaf;
}

HuffNode *HuffNode::get_left() {
    return HuffNode::left;
}

HuffNode *HuffNode::get_right() {
    return HuffNode::right;
}

void debug_tree(HuffNode *tree, std::string code) {
    auto log = Logger::GetInstance();

    if (!tree) {
        // base case.
        return;
    }

    if (tree->is_leaf()) {
        // it's a node with characters
        code.push_back(tree->get_char());
        log->Log(code, LogLevel::DEBUG);
    }

    // recursive calls
    debug_tree(tree->get_left(), code + "0");
    debug_tree(tree->get_right(), code + "1");
}
