#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
 using namespace std ;
class huffman_codec{
 public:
  huffman_codec(){
   
  }
  bool compress(const string& inputfile , const string& outputfile){
    cout<<"compressing"<<inputfile<<"To"<<outputfile;
    return true ;
  }
  bool decompress(const string&inputfile , const string& outputfile){
    cout<<"decompressing"<<inputfile<<"to"<<outputfile;
    return true ;
  }
};

void print_help(){
    cout<<"~~~~~ HUFFMAN FILE COMPRESSOR ~~~~~~~"<<endl;
    cout<<"Usage for the compressor details"<<endl;
    cout << "  ./compressor --compress <input_file> <output_file>\n";
    cout << "  ./compressor --decompress <input_file> <output_file>\n";
    cout << "  ./compressor --help\n\n";
    
    cout<<"options:   "<<endl;
    cout<<" --compress    : compresses a file using the huffman method"<<endl;
    cout<<" --decompress  : decompresses a huffman file"<<endl;
    cout<<" --help        : display this help message"<<endl ;

    cout<<"\n example \n"<<endl;
    cout << "  ./compressor --compress document.txt document.huff\n";
    cout << "  ./compressor --decompress document.huff document.txt\n\n";
}
    
int main(int argc , char* argv[]){
    if (argc == 1 || (argc >= 2 && strcmp(argv[1], "--help") == 0)) {
    print_help();
    return 0;
} 
 if (argc<4){
    cerr<<"error please enter the valid commands"<<endl ;
    print_help();
    return 1 ;
 }
    string mode = argv[1];
    string inputfile = argv[2];
    string outputfile = argv[3];

    huffman_codec codec ;
    if(mode=="-- compress"){
        cout<<"\t ----starting compression....---- \t "<<endl ;
        if(codec.compress(inputfile,outputfile)){
            cout<<"[sucess] File has been compressed"<<endl;
        }
        else {
            cerr<<"compression failed"<<endl;
            return 1 ;

        }
    }
    else if (mode=="-- decompress"){
        cout<<"\t --starting decompression--";
        if(codec.decompress(inputfile,outputfile)){
            cout<<"[sucess] decompression is done";
        }
            else {
                cerr<<"error in decompression";
                return 1 ;
            }
        }
        else {
            cerr<<"\n[error] unknown mode!!"<<mode<<endl;
            cerr<<"use only --help ,--compress,--decompress"<<endl; 
            return 1 ;

        }
        return 0 ;
    }
