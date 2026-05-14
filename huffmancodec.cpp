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
    
    // Error check: input file exists
    string content;
    if (!readFile(inputFile, content)) {
        cerr << "Error: Could not read input file '" << inputFile << "'!" << endl;
        return;
    }
    
    // Error check: empty file
    if (content.empty()) {
        cerr << "Warning: Input file is empty!" << endl;
        // Create empty output
        vector<bool> emptyBits;
        writeBinaryFile(outputFile, emptyBits);
        cout << "Created empty compressed file" << endl;
        return;
    }
    
    cout << "Read " << content.length() << " characters" << endl;
    cout << "Content: \"" << content.substr(0, 50) << (content.length() > 50 ? "..." : "") << "\"" << endl;
    
    // Count frequencies
    unordered_map<char, int> frequencies;
    for (char c : content) {
        frequencies[c]++;
    }
    
    cout << "\n=== FREQUENCIES ===" << endl;
    cout << "Unique characters: " << frequencies.size() << endl;
    
    // Handle special case: only one unique character
    if (frequencies.size() == 1) {
        cout << "Special case: Only one unique character" << endl;
        // Create simple encoding: just store the character and count
        ofstream file(outputFile, ios::binary);
        int marker = -1;  // Special marker for single char
        file.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
        char c = content[0];
        file.write(&c, 1);
        int length = content.length();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.close();
        
        // Save tree
        saveTree(outputFile + ".tree");
        cout << "\n=== ENCODING COMPLETE (Single character optimization) ===" << endl;
        return;
    }
    
    // Build Huffman tree
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
    
    // Generate codes
    huffmanCodes.clear();
    cout << "\n=== HUFFMAN CODES ===" << endl;
    generateCodes(root, "");
    
    // Encode to binary
    string binaryString = "";
    for (char c : content) {
        if (huffmanCodes.find(c) == huffmanCodes.end()) {
            cerr << "Error: Character '" << c << "' not found in Huffman codes!" << endl;
            return;
        }
        binaryString += huffmanCodes[c];
    }
    
    cout << "\n=== ENCODED OUTPUT ===" << endl;
    cout << "Original size: " << content.length() << " bytes (" 
         << content.length() * 8 << " bits)" << endl;
    cout << "Compressed size: " << binaryString.length() << " bits" << endl;
    
    if (content.length() * 8 > 0) {
        double ratio = (binaryString.length() * 100.0) / (content.length() * 8);
        cout << "Compression ratio: " << ratio << "%" << endl;
    }
    
    // Convert to bits and write
    vector<bool> bits;
    for (char c : binaryString) {
        bits.push_back(c == '1');
    }
    
    if (!writeBinaryFile(outputFile, bits)) {
        cerr << "Error: Could not write output file!" << endl;
        return;
    }
    
<<<<<<< HEAD
    // Save the tree
=======
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
    string treeFile = outputFile + ".tree";
    saveTree(treeFile);
    
    cout << "\n=== ENCODING COMPLETE ===" << endl;
}

void HuffmanCodec::decode(const string& inputFile, const string& outputFile) {
    cout << "\n=== DECODING START ===" << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    
<<<<<<< HEAD
    // Check if input file exists
    ifstream check(inputFile, ios::binary);
    if (!check.is_open()) {
        cerr << "Error: Input file '" << inputFile << "' does not exist!" << endl;
        return;
    }
    check.close();
    
    // Check for single character special case
    ifstream test(inputFile, ios::binary);
    int marker;
    test.read(reinterpret_cast<char*>(&marker), sizeof(marker));
    test.close();
    
    if (marker == -1) {
        cout << "Detected single-character encoding" << endl;
        ifstream file(inputFile, ios::binary);
        file.read(reinterpret_cast<char*>(&marker), sizeof(marker));
        char c;
        file.read(&c, 1);
        int length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        file.close();
        
        string decodedText(length, c);
        writeFile(outputFile, decodedText);
        cout << "Decoded " << length << " characters of '" << c << "'" << endl;
        cout << "\n=== DECODING COMPLETE ===" << endl;
        return;
    }
    
    // Normal decoding
    vector<bool> bits;
    if (!readBinaryFile(inputFile, bits)) {
        cerr << "Error: Could not read binary file!" << endl;
=======
    vector<bool> bits;
    if (!readBinaryFile(inputFile, bits)) {
        cerr << "Error: Could not read input file!" << endl;
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
        return;
    }
    
    cout << "Read " << bits.size() << " bits from compressed file" << endl;
    
<<<<<<< HEAD
    if (bits.empty()) {
        cout << "Empty compressed file, creating empty output" << endl;
        writeFile(outputFile, "");
        return;
    }
    
=======
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
    if (!root) {
        cerr << "Error: No Huffman tree available! Please load tree first." << endl;
        return;
    }
    
<<<<<<< HEAD
    // Decode the bits
    string decodedText = "";
    HuffmanNode* current = root;
    int bitsProcessed = 0;
=======
    string decodedText = "";
    HuffmanNode* current = root;
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
    
    cout << "\n=== DECODING PROCESS ===" << endl;
    
    for (size_t i = 0; i < bits.size(); i++) {
<<<<<<< HEAD
        // Navigate the tree
        if (bits[i] == 0) {
            if (current->left) {
                current = current->left;
            } else {
                cerr << "Error: Invalid bit sequence at position " << i << " (no left child)" << endl;
                return;
            }
        } else {
            if (current->right) {
                current = current->right;
            } else {
                cerr << "Error: Invalid bit sequence at position " << i << " (no right child)" << endl;
=======
        if (bits[i] == 0) {
            if (current->left) current = current->left;
            else {
                cerr << "Error: Invalid bit at position " << i << endl;
                return;
            }
        } else {
            if (current->right) current = current->right;
            else {
                cerr << "Error: Invalid bit at position " << i << endl;
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
                return;
            }
        }
        
<<<<<<< HEAD
        // Check if we've reached a leaf
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character;
            bitsProcessed++;
            if (bitsProcessed <= 10) {  // Show first 10 characters only
                cout << "Found character '" << current->character << "' at bit position " << i << endl;
            }
            current = root;  // Reset to root for next character
        }
    }
    
    if (bitsProcessed > 10) {
        cout << "... and " << (bitsProcessed - 10) << " more characters" << endl;
    }
    
    cout << "\n=== DECODING COMPLETE ===" << endl;
    cout << "Decoded " << decodedText.length() << " characters" << endl;
    cout << "Decoded text preview: \"" << decodedText.substr(0, 50) 
         << (decodedText.length() > 50 ? "..." : "") << "\"" << endl;
=======
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->character;
            cout << "Found character '" << current->character << "' at bit position " << i << endl;
            current = root;
        }
    }
    
    cout << "\n=== DECODING COMPLETE ===" << endl;
    cout << "Decoded " << decodedText.length() << " characters" << endl;
    cout << "Decoded text: \"" << decodedText << "\"" << endl;
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
    
    if (!writeFile(outputFile, decodedText)) {
        cerr << "Error: Could not write output file!" << endl;
        return;
    }
    
    cout << "Successfully wrote decoded text to: " << outputFile << endl;
<<<<<<< HEAD
}bool HuffmanCodec::readFile(const string& filename, string& content) {
=======
}

bool HuffmanCodec::readFile(const string& filename, string& content) {
>>>>>>> 44c41e3be068bf4fb473ee1a9a88dea61a0cbea2
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
    
    int totalBits = bits.size();
    file.write(reinterpret_cast<const char*>(&totalBits), sizeof(totalBits));
    
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
    
    int totalBits = 0;
    file.read(reinterpret_cast<char*>(&totalBits), sizeof(totalBits));
    
    vector<char> bytes;
    char byte;
    while (file.read(&byte, 1)) {
        bytes.push_back(byte);
    }
    file.close();
    
    bits.clear();
    bits.reserve(totalBits);
    
    for (size_t i = 0; i < bytes.size() && bits.size() < totalBits; i++) {
        for (int j = 7; j >= 0 && bits.size() < totalBits; j--) {
            bits.push_back((bytes[i] >> j) & 1);
        }
    }
    
    return true;
}

void HuffmanCodec::saveTreeToFile(ofstream& file, HuffmanNode* node) {
    if (!node) {
        char marker = '#';
        file.write(&marker, 1);
        return;
    }
    
    if (node->character != '\0') {
        char marker = 'L';
        file.write(&marker, 1);
        file.write(&node->character, 1);
    } else {
        char marker = 'I';
        file.write(&marker, 1);
        saveTreeToFile(file, node->left);
        saveTreeToFile(file, node->right);
    }
}

void HuffmanCodec::saveTree(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not save tree!" << endl;
        return;
    }
    saveTreeToFile(file, root);
    file.close();
    cout << "Tree saved to: " << filename << endl;
}

void HuffmanCodec::loadTreeFromFile(ifstream& file, HuffmanNode*& node) {
    char marker;
    file.read(&marker, 1);
    
    if (marker == '#') {
        node = nullptr;
        return;
    }
    
    if (marker == 'L') {
        char ch;
        file.read(&ch, 1);
        node = new HuffmanNode(ch, 0);
    } else if (marker == 'I') {
        node = new HuffmanNode('\0', 0);
        loadTreeFromFile(file, node->left);
        loadTreeFromFile(file, node->right);
    }
}

void HuffmanCodec::loadTree(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not load tree!" << endl;
        return;
    }
    deleteTree(root);
    loadTreeFromFile(file, root);
    file.close();
    cout << "Tree loaded from: " << filename << endl;
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