#include "huffmancodec.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    cout << "=== HUFFMAN CODEC FULL TEST ===" << endl;
    
  
    ofstream testFile("original.txt");
    testFile << "hello world this is a test of huffman compression";
    testFile.close();
    cout << "Created original.txt" << endl;
    
 
    HuffmanCodec encoder;
    cout << "\n--- ENCODING ---" << endl;
    encoder.encode("original.txt", "compressed.huff");
    
    
    HuffmanCodec decoder;
    cout << "\n--- DECODING ---" << endl;
    decoder.loadTree("compressed.huff.tree");
    decoder.decode("compressed.huff", "decoded.txt");
    cout << "\n=== VERIFICATION ===" << endl;
    
    ifstream original("original.txt");
    ifstream decoded("decoded.txt");
    
    string originalContent, decodedContent;
    original >> originalContent;
    decoded >> decodedContent;
    
    if (originalContent == decodedContent) {
        cout << "✅ SUCCESS! Decoded text matches original!" << endl;
    } else {
        cout << "❌ FAILURE! Decoded text doesn't match original." << endl;
        cout << "Original: " << originalContent << endl;
        cout << "Decoded:  " << decodedContent << endl;
    }
    
    return 0;
}