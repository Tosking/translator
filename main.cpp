#include <iostream>
#include <fstream>
#include <string>
#include "translator.h"
using namespace std;


int main(int argc, char *argv[]) {
    ifstream f;
    f.open("test.cpp", ifstream::in);
    string str;
    string buff;
    while(getline(f, buff)){
        str += buff;
        str += "\n";
    }
    Translator translator(str);
    cout << translator.delete_comments() << endl;


    return 0;
}
