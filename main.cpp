#include <iostream>
#include <fstream>
#include <string>
#include "translator.h"
using namespace std;


int main(int argc, char *argv[]) {
    Translator translator("test.cpp");
    cout << translator.delete_comments() << endl;


    return 0;
}
