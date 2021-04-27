#include<iostream>
#include<fstream>

using namespace std;

string createDestMapping(string rawKey) {
        string s = "";
        
        for(char c: rawKey) {
                if(s.find(c) == string::npos) {
                        s += c;
                }
        }
        
        for(int i=0; i<10; i++) {
                char c = (char)('0' + (10 - i - 1));

                if(s.find(c) == string::npos) {
                        s += c;
                }
        }
        for(int i=0; i<26; i++) {
                char c = (char)('A' + (26 - i - 1));

                if(s.find(c) == string::npos) {
                        s += c;
                }
        }
        return s;
}

string createSourceMapping() {
        string s = "";
        for(int i=0; i<26; i++) {
                s += (char)('A' + i);
        }
        for(int i=0; i<10; i++) {
                s += (char)('0' + i);
        }
        return s;
}

void convertFile(string sourceFile, string destFile, string sourceMapping, string destMapping) {
        ifstream input(sourceFile.c_str());
        ofstream output(destFile.c_str());
        
        cout << "Source: " << sourceMapping << endl;
        cout << "Dest: " << destMapping << endl;
        
        char ch;

        while (input >> noskipws >> ch) {
                        
                if(isalpha(ch) && isupper(ch)) {
                        int index = sourceMapping.find(ch);
                        output << (char)destMapping[index];
                } else if(isalpha(ch) && islower(ch)) {
                        int index = sourceMapping.find(toupper(ch));
                        output << (char)tolower(destMapping[index]);
                } else if(isdigit(ch)) {
                        int index = sourceMapping.find(ch);
                        output << (char)destMapping[index];
                } else {
                        output << ch;
                }
        }

        input.close();
        output.close();
}



int main(int argc, const char* argv[]) {

    
    short actionNumber; 
    int errorCode = 0; 
    string rawKey; //The key used for encryption or decryption, without duplicates removed
    string sourceFilename; //File to read from
    string destinationFilename; //File to write to

    if ( argc != 5 ) {
        //Invalid number of arguments at the command line
        errorCode = 1;
    } else {
        string actionString = argv[1];
        //Read action
        if ( actionString == "-d" )
            actionNumber = 1; //decrypt
        else if ( actionString == "-e" )
            actionNumber = 2; //encrypt
        else {
            errorCode = 2;
        }
    }
    if (errorCode == 0) {
        //Get key
        rawKey = argv[2];
        if ( rawKey.length() > 2 && rawKey.substr(0,2) == "-k" )
            rawKey.erase(0,2);
        else
            errorCode = 3;
    }
    if (errorCode == 0) {
        sourceFilename =  argv[3];
        destinationFilename = argv[4];
    }
        
    if ( errorCode == 0 ) {
        //Do work here, command line was successfully parsed

        if(actionNumber == 1) {
                convertFile(sourceFilename, destinationFilename, createSourceMapping(), createDestMapping(rawKey));
        } else if(actionNumber == 2) {
                convertFile(sourceFilename, destinationFilename, createDestMapping(rawKey), createSourceMapping());
        }

    } else {
        cerr << "Usage: " << argv[0] << " (-e|-d) -kKEY source_filename destination_filename" << endl;
    }

    return errorCode;
}