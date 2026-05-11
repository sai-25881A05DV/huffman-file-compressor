
#ifndef HUFFMAN_CODEC_H
#define HUFFMAN_CODEC_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

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
    
    std::unordered_map<char, std::string> huffmanCodes;
    HuffmanNode* root;
    
    
    void generateCodes(HuffmanNode* node, const std::string& code);
    void deleteTree(HuffmanNode* node);
    
public:
    
    HuffmanCodec();
    ~HuffmanCodec();
    

    void encode(const std::string& inputFile, const std::string& outputFile);
    void decode(const std::string& inputFile, const std::string& outputFile);
    

    bool readFile(const std::string& filename, std::string& content);
    bool writeFile(const std::string& filename, const std::string& content);
    bool writeBinaryFile(const std::string& filename, const std::vector<bool>& bits);
    bool readBinaryFile(const std::string& filename, std::vector<bool>& bits);
    
    
    double getCompressionRatio() const;
    size_t getOriginalSize() const;
    size_t getCompressedSize() const;
    void printStatistics() const;
    
    
    void buildFrequencyTable(const std::string& content);
    void buildHuffmanTree();
    void generateHuffmanCodes();
};

#endif 