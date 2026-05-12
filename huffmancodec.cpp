#include "huffmancodec.h"
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

HuffmanCodec::HuffmanCodec() : root(nullptr) {}

HuffmanCodec::~HuffmanCodec() {
    deleteTree(root);
}

void HuffmanCodec::buildFrequencyTable(const string& content) {
    unordered_map<char, int> freqTable;
    
    for (char c : content) {
        freqTable[c]++;
    }
    
    cout << "\n=== FREQUENCY TABLE ===" << endl;
    for (auto& pair : freqTable) {
        cout << "'" << pair.first << "' : " << pair.second << " times" << endl;
    }
}

void HuffmanCodec::generateCodes(HuffmanNode* node, const string& code) {
    if (!node) return;
    
    if (node->character != '\0') {
        huffmanCodes[node->character] = code;
        cout << "'" << node->character << "' => " << code << endl;
        return;
    }
    
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCodec::generateHuffmanCodes() {
    generateCodes(root, "");
}

void HuffmanCodec::encode(const string& inputFile, const string& outputFile) {
    cout << "\n=== ENCODING START ===" << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    
    string content;
    if (!readFile(inputFile, content)) {
        cerr << "Error: Could not read input file!" << endl;
        return;
    }
    
    cout << "Read " << content.length() << " characters" << endl;
    cout << "Content: \"" << content << "\"" << endl;
    
    unordered_map<char, int> frequencies;
    for (char c : content) {
        frequencies[c]++;
    }
    
    cout << "\n=== FREQUENCIES ===" << endl;
    for (auto& pair : frequencies) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
    
    auto cmp = [](HuffmanNode* left, HuffmanNode* right) { 
        return left->frequency > right->frequency; 
    };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> pq(cmp);
    
    for (auto& pair : frequencies) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }
    
    cout << "\n=== BUILDING HUFFMAN TREE ===" << endl;
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
        
        cout << "Combined " << left->frequency << " + " << right->frequency 
             << " = " << parent->frequency << endl;
    }
    
    root = pq.top();
    
    huffmanCodes.clear();
    cout << "\n=== HUFFMAN CODES ===" << endl;
    generateCodes(root, "");
    
    string binaryString = "";
    for (char c : content) {
        binaryString += huffmanCodes[c];
    }
    
    cout << "\n=== ENCODED OUTPUT ===" << endl;
    cout << "Original: " << content << endl;
    cout << "Binary:   " << binaryString << endl;
    cout << "Original size: " << content.length() << " bytes (" 
         << content.length() * 8 << " bits)" << endl;
    cout << "Compressed size: " << binaryString.length() << " bits" << endl;
    
    if (content.length() * 8 > 0) {
        cout << "Compression ratio: " << (binaryString.length() * 100.0) / (content.length() * 8) 
             << "%" << endl;
    }
    
    vector<bool> bits;
    for (char c : binaryString) {
        bits.push_back(c == '1');
    }
    
    if (!writeBinaryFile(outputFile, bits)) {
        cerr << "Error: Could not write output file!" << endl;
        return;
    }
    
    cout << "\n=== ENCODING COMPLETE ===" << endl;
}

void HuffmanCodec::decode(const string& inputFile, const string& outputFile) {
    cout << "Decode function - Coming in Day 4!" << endl;
}

bool HuffmanCodec::readFile(const string& filename, string& content) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    content = string((istreambuf_iterator<char>(file)), 
                      istreambuf_iterator<char>());
    file.close();
    return true;
}

bool HuffmanCodec::writeFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

bool HuffmanCodec::writeBinaryFile(const string& filename, const vector<bool>& bits) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    char buffer = 0;
    int bitCount = 0;
    
    for (bool bit : bits) {
        buffer = (buffer << 1) | (bit ? 1 : 0);
        bitCount++;
        
        if (bitCount == 8) {
            file.write(&buffer, 1);
            buffer = 0;
            bitCount = 0;
        }
    }
    
    if (bitCount > 0) {
        buffer = buffer << (8 - bitCount);
        file.write(&buffer, 1);
    }
    
    file.close();
    return true;
}

bool HuffmanCodec::readBinaryFile(const string& filename, vector<bool>& bits) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    char byte;
    while (file.read(&byte, 1)) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((byte >> i) & 1);
        }
    }
    
    file.close();
    return true;
}

double HuffmanCodec::getCompressionRatio() const {
    return 0.0;
}

size_t HuffmanCodec::getOriginalSize() const {
    return 0;
}

size_t HuffmanCodec::getCompressedSize() const {
    return 0;
}

void HuffmanCodec::printStatistics() const {
    cout << "Compression statistics will be shown here." << endl;
}

void HuffmanCodec::buildHuffmanTree() {
}

void HuffmanCodec::deleteTree(HuffmanNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}