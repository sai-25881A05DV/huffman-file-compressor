#include "huffmancodec.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    cout << "=== TEST DECODING 'hello' ===" << endl;
    
    // Create and encode "hello"
    ofstream helloFile("hello.txt");
    helloFile << "hello";
    helloFile.close();
    
    HuffmanCodec encoder;
    encoder.encode("hello.txt", "hello.huff");
    
    // Create new decoder and load tree
    HuffmanCodec decoder;
    decoder.loadTree("hello.huff.tree");
    
    // Decode
    decoder.decode("hello.huff", "hello_decoded.txt");
    
    // Verify
    ifstream decoded("hello_decoded.txt");
    string result;
    getline(decoded, result);
    
    cout << "\n=== RESULT ===" << endl;
    cout << "Expected: hello" << endl;
    cout << "Got:      " << result << endl;
    
    if (result == "hello") {
        cout << "✅ DECODE SUCCESSFUL! Original text recovered!" << endl;
    } else {
        cout << "❌ DECODE FAILED!" << endl;
    }
    
    return 0;
}