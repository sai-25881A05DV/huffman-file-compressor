#include "huffmancodec.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

void print_help() {
    cout<<"\n~~~~~ HUFFMAN FILE COMPRESSOR ~~~~~~~"<<endl;
    cout<<"======================================"<<endl;
    cout<<"Usage:"<<endl;
    cout<<"  ./compressor --compress <input_file> <output_file>"<<endl;
    cout<<"  ./compressor --decompress <input_file> <output_file>"<<endl;
    cout<<"  ./compressor --help"<<endl;
    cout<<"\nOptions:"<<endl;
    cout<<"  --compress    : Compresses a file using Huffman coding"<<endl;
    cout<<"  --decompress  : Decompresses a Huffman compressed file"<<endl;
    cout<<"  --help        : Display this help message"<<endl;
    cout<<"\nExamples:"<<endl;
    cout<<"  ./compressor --compress document.txt document.huff"<<endl;
    cout<<"  ./compressor --decompress document.huff document.txt"<<endl;
    cout<<"======================================\n"<<endl;
}

int main(int argc, char* argv[]) {
    // Check for help
    if (argc == 1 || (argc >= 2 && strcmp(argv[1], "--help") == 0)) {
        print_help();
        return 0;
    } 
    
    // Check minimum arguments
    if (argc < 4) {
        cerr<<"\n[ERROR] Invalid number of arguments!"<<endl;
        print_help();
        return 1;
    }
    
    string mode = argv[1];
    string inputfile = argv[2];
    string outputfile = argv[3];
    
    // Fix: Remove space from "--compress" and "--decompress"
    if (mode == "--compress") {
        cout<<"\n\t===== STARTING COMPRESSION ====="<<endl;
        cout<<"Input file:  "<<inputfile<<endl;
        cout<<"Output file: "<<outputfile<<endl;
        
        HuffmanCodec codec;
        codec.encode(inputfile, outputfile);
        
        cout<<"\n[SUCCESS] File compressed successfully!"<<endl;
        
    } 
    else if (mode == "--decompress") {
        cout<<"\n\t===== STARTING DECOMPRESSION ====="<<endl;
        cout<<"Input file:  "<<inputfile<<endl;
        cout<<"Output file: "<<outputfile<<endl;
        
        HuffmanCodec codec;
        
        // Load the tree file (same name as input + ".tree")
        string treeFile = inputfile + ".tree";
        codec.loadTree(treeFile);
        
        codec.decode(inputfile, outputfile);
        
        cout<<"\n[SUCCESS] File decompressed successfully!"<<endl;
    } 
    else {
        cerr<<"\n[ERROR] Unknown mode: "<<mode<<endl;
        cerr<<"Use --help, --compress, or --decompress"<<endl;
        return 1;
    }
    
    return 0;
}