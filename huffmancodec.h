#ifndef HUFFMAN_CODEC_H
#define HUFFMAN_CODEC_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <queue>
#include <iostream>

using namespace std;

class HuffmanCodec {
private:
    struct HuffmanNode {
        char character;
        int frequency;
        HuffmanNode* left;
        HuffmanNode* right;
        
        HuffmanNode(char ch, int freq) 
            : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    };
    
    struct CompareNode {
        bool operator()(HuffmanNode* a, HuffmanNode* b) {
            return a->frequency > b->frequency;
        }
    };
    
    unordered_map<char, string> huffmanCodes;
    HuffmanNode* root;
    
    void generateCodes(HuffmanNode* node, const string& code);
    void deleteTree(HuffmanNode* node);
    
public:
    HuffmanCodec();
    ~HuffmanCodec();
    
    void encode(const string& inputFile, const string& outputFile);
    void decode(const string& inputFile, const string& outputFile);
    
    bool readFile(const string& filename, string& content);
    bool writeFile(const string& filename, const string& content);
    bool writeBinaryFile(const string& filename, const vector<bool>& bits);
    bool readBinaryFile(const string& filename, vector<bool>& bits);
    
    double getCompressionRatio() const;
    size_t getOriginalSize() const;
    size_t getCompressedSize() const;
    void printStatistics() const;
    
    void buildFrequencyTable(const string& content);
    void buildHuffmanTree();
    void generateHuffmanCodes();
    
    // Tree save/load functions - ADD THESE
    void saveTree(const string& filename);
    void loadTree(const string& filename);
    void saveTreeToFile(ofstream& file, HuffmanNode* node);
    void loadTreeFromFile(ifstream& file, HuffmanNode*& node);
};

#endif