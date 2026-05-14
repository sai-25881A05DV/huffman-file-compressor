#include "huffmancodec.h"
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// Helper function to compare two files
bool compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open()) return false;
    
    string content1((istreambuf_iterator<char>(f1)), istreambuf_iterator<char>());
    string content2((istreambuf_iterator<char>(f2)), istreambuf_iterator<char>());
    
    return content1 == content2;
}

// Test 1: Basic hello world
void testBasic() {
    cout << "\n=== TEST 1: Basic String ===" << endl;
    
    // Create test file
    ofstream input("test_basic.txt");
    input << "hello world";
    input.close();
    
    // Encode
    HuffmanCodec encoder;
    encoder.encode("test_basic.txt", "test_basic.huff");
    
    // Decode
    HuffmanCodec decoder;
    decoder.loadTree("test_basic.huff.tree");
    decoder.decode("test_basic.huff", "test_basic_decoded.txt");
    
    // Verify
    if (compareFiles("test_basic.txt", "test_basic_decoded.txt")) {
        cout << "✅ Basic test PASSED" << endl;
    } else {
        cout << "❌ Basic test FAILED" << endl;
    }
}

// Test 2: Empty file
void testEmpty() {
    cout << "\n=== TEST 2: Empty File ===" << endl;
    
    // Create empty file
    ofstream input("test_empty.txt");
    input << "";
    input.close();
    
    // Encode
    HuffmanCodec encoder;
    encoder.encode("test_empty.txt", "test_empty.huff");
    
    // Decode
    HuffmanCodec decoder;
    decoder.loadTree("test_empty.huff.tree");
    decoder.decode("test_empty.huff", "test_empty_decoded.txt");
    
    // Verify
    if (compareFiles("test_empty.txt", "test_empty_decoded.txt")) {
        cout << "✅ Empty file test PASSED" << endl;
    } else {
        cout << "❌ Empty file test FAILED" << endl;
    }
}

// Test 3: Single character repeated
void testSingleChar() {
    cout << "\n=== TEST 3: Single Character Repeated ===" << endl;
    
    ofstream input("test_single.txt");
    input << "aaaaaaaaaa";  // 10 'a's
    input.close();
    
    HuffmanCodec encoder;
    encoder.encode("test_single.txt", "test_single.huff");
    
    HuffmanCodec decoder;
    decoder.loadTree("test_single.huff.tree");
    decoder.decode("test_single.huff", "test_single_decoded.txt");
    
    if (compareFiles("test_single.txt", "test_single_decoded.txt")) {
        cout << "✅ Single character test PASSED" << endl;
    } else {
        cout << "❌ Single character test FAILED" << endl;
    }
}

// Test 4: Only two unique characters
void testTwoChars() {
    cout << "\n=== TEST 4: Two Characters Only ===" << endl;
    
    ofstream input("test_two.txt");
    input << "ababababab";
    input.close();
    
    HuffmanCodec encoder;
    encoder.encode("test_two.txt", "test_two.huff");
    
    HuffmanCodec decoder;
    decoder.loadTree("test_two.huff.tree");
    decoder.decode("test_two.huff", "test_two_decoded.txt");
    
    if (compareFiles("test_two.txt", "test_two_decoded.txt")) {
        cout << "✅ Two characters test PASSED" << endl;
    } else {
        cout << "❌ Two characters test FAILED" << endl;
    }
}

// Test 5: Large text
void testLarge() {
    cout << "\n=== TEST 5: Large Text ===" << endl;
    
    ofstream input("test_large.txt");
    for (int i = 0; i < 100; i++) {
        input << "The quick brown fox jumps over the lazy dog. ";
    }
    input.close();
    
    HuffmanCodec encoder;
    encoder.encode("test_large.txt", "test_large.huff");
    
    HuffmanCodec decoder;
    decoder.loadTree("test_large.huff.tree");
    decoder.decode("test_large.huff", "test_large_decoded.txt");
    
    if (compareFiles("test_large.txt", "test_large_decoded.txt")) {
        cout << "✅ Large text test PASSED" << endl;
    } else {
        cout << "❌ Large text test FAILED" << endl;
    }
}

// Test 6: Special characters
void testSpecialChars() {
    cout << "\n=== TEST 6: Special Characters ===" << endl;
    
    ofstream input("test_special.txt");
    input << "Hello! @#$%^&*() 12345 \n\tNew line";
    input.close();
    
    HuffmanCodec encoder;
    encoder.encode("test_special.txt", "test_special.huff");
    
    HuffmanCodec decoder;
    decoder.loadTree("test_special.huff.tree");
    decoder.decode("test_special.huff", "test_special_decoded.txt");
    
    if (compareFiles("test_special.txt", "test_special_decoded.txt")) {
        cout << "✅ Special characters test PASSED" << endl;
    } else {
        cout << "❌ Special characters test FAILED" << endl;
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "   COMPLETE ENCODE-DECODE CYCLE TEST" << endl;
    cout << "========================================" << endl;
    
    testBasic();
    testEmpty();
    testSingleChar();
    testTwoChars();
    testLarge();
    testSpecialChars();
    
    cout << "\n========================================" << endl;
    cout << "           ALL TESTS COMPLETE" << endl;
    cout << "========================================" << endl;
    
    return 0;
}