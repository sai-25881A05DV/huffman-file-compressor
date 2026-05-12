#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
using namespace std;

struct HuffmanNode
{
    char data;
    int frequency;

    HuffmanNode* left;
    HuffmanNode* right;
};
class HuffmanTree
{
public:
    void buildTree();
    void generateCodes();
};

#endif
