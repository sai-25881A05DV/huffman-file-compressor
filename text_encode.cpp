#include "huffmancodec.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    cout << "=== HUFFMAN ENCODE TEST ===" << endl;
    
    ofstream testFile("hello.txt");
    testFile << "hello";
    testFile.close();
    
    cout << "Created 'hello.txt' with content: hello" << endl;
    
    
    HuffmanCodec codec;
    codec.encode("hello.txt", "hello.huff");
    
    cout << "\n✅ Successfully encoded 'hello' to binary!" << endl;
    return 0;
}