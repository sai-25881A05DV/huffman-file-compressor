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

void runCompress(const string& inputfile, const string& outputfile) {
    cout<<"\n\t===== STARTING COMPRESSION ====="<<endl;
    cout<<"Input file:  "<<inputfile<<endl;
    cout<<"Output file: "<<outputfile<<endl;

    HuffmanCodec codec;
    codec.encode(inputfile, outputfile);

    cout<<"\n[SUCCESS] File compressed successfully!"<<endl;
    codec.printStatistics();
}

void runDecompress(const string& inputfile, const string& outputfile) {
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

void print_menu() {
    cout<<"\n======================================"<<endl;
    cout<<"~~~~~ HUFFMAN FILE COMPRESSOR ~~~~~~~"<<endl;
    cout<<"======================================"<<endl;
    cout<<"1. Compress a file"<<endl;
    cout<<"2. Decompress a file"<<endl;
    cout<<"3. Help"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"======================================"<<endl;
    cout<<"Enter choice: ";
}

void runInteractiveMenu() {
    while (true) {
        print_menu();
        string choiceStr;
        getline(cin, choiceStr);

        if (choiceStr == "1") {
            string inputfile, outputfile;
            cout<<"Enter input file path: ";
            getline(cin, inputfile);
            cout<<"Enter output file path (e.g. output.huff): ";
            getline(cin, outputfile);
            try {
                runCompress(inputfile, outputfile);
            } catch (const exception& e) {
                cerr<<"\n[ERROR] "<<e.what()<<endl;
            }
        }
        else if (choiceStr == "2") {
            string inputfile, outputfile;
            cout<<"Enter compressed file path (e.g. output.huff): ";
            getline(cin, inputfile);
            cout<<"Enter output file path (e.g. restored.txt): ";
            getline(cin, outputfile);
            try {
                runDecompress(inputfile, outputfile);
            } catch (const exception& e) {
                cerr<<"\n[ERROR] "<<e.what()<<endl;
            }
        }
        else if (choiceStr == "3") {
            print_help();
        }
        else if (choiceStr == "4") {
            cout<<"\nGoodbye!\n"<<endl;
            break;
        }
        else {
            cout<<"\n[ERROR] Invalid choice. Please enter 1, 2, 3, or 4.\n"<<endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // No arguments: launch interactive menu
    if (argc == 1) {
        runInteractiveMenu();
        return 0;
    }

    // Check for help
    if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
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
        runCompress(inputfile, outputfile);
    } 
    else if (mode == "--decompress") {
        runDecompress(inputfile, outputfile);
    } 
    else {
        cerr<<"\n[ERROR] Unknown mode: "<<mode<<endl;
        cerr<<"Use --help, --compress, or --decompress"<<endl;
        return 1;
    }
    
    return 0;
}
