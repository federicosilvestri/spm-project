//
// Created by federicosilvestri on 13/10/23.
//

#ifndef SPM_PROJECT_HUFFMAN_TREE_HPP
#define SPM_PROJECT_HUFFMAN_TREE_HPP
#define HUFF_ESCAPE_CHAR '#'
#include "string"

/**
 * @brief Huffman Binary Tree Class.
 */
class HuffNode {
    // Payload
    /**
     * @brief flag to identify up nodes.
     */
    bool leaf;

    /**
     * @brief Represented character
     */
    unsigned char character;
    /**
     * @brief Frequency related to the represented character.
     */
    unsigned int freq;


    // Recursive declaration of tree.
    /**
     * @brief left tree or leaf
     */
    HuffNode *left;
    // right tree or leaf
    HuffNode *right;

public:
    /**
     * @brief Create a node
     * @param character the character represented by node
     * @param freq the frequency
     * @param left the left node, default is nullptr
     * @param right the right node, default is nullptr
     * @param leaf flag that indicates that node contains character info.
     */
    HuffNode(unsigned char character, unsigned int freq, HuffNode *left = nullptr, HuffNode *right = nullptr, bool leaf = true);

    /**
     * @brief Destructor for the object.
     */
    ~HuffNode();

    /**
     * @brief Get the encapsulated value of frequency.
     * @return the integer value of frequency
     */
    unsigned int get_freq();

    /**
     * @brief Get the character for this node, if it is not an "up" Node.
     * @return character value.
     */
    unsigned char get_char();

    /**
     * @brief Return true if the node is a leaf, and than contains a character.
     * @return true if it is a leaf.
     */
    bool is_leaf();

    /**
     * @brief Get the left node
     * @return The left node
     */
    HuffNode *get_left();

    /**
     * @brief Get the right node
     * @return The right node
     */
    HuffNode *get_right();

};


/**
 * @brief Compare two node, the node, such that op == true iff a.freq > b.freq
 */
class CompareHuffNodes {
public:
    bool operator()(HuffNode *a, HuffNode *b) {
        return a->get_freq() > b->get_freq();
    }
};

/**
 * @brief Log the tree as text
 * @param tree The tree to be debugged.
 */
void debug_tree(HuffNode *tree, std::string code);

#endif //SPM_PROJECT_HUFFMAN_TREE_HPP
