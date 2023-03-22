#include "translator.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Translator::Translator(string input){
    this->input = input;
}

string Translator::delete_comments(){
    ifstream file;
    file.open(this->input, ifstream::in);
    char ch;
    State state = Normal;
    string result = "";
    while(file.get(ch)){
        switch(state){
            case Slash:
                if(ch == '*'){
                    state = Comment_Star;
                    break;
                }
                result += ch;
                state = Normal;
                break;
            case Star:
                if(ch == '/'){
                    state = Normal;
                    break;
                }
                else if(ch == '*'){
                    break;
                }
                break;
            case Comment_Star:
                if(ch == '*'){
                    state = Star;
                }
                break;
            case Comment_Slash:
                if(ch == '\n'){
                    state = Normal;
                }
                break;

            case Normal:
                switch(ch){
                    case '/':
                        state = Slash;
                        break;
                    case '*':
                        state = Star;
                        break;
                    default:
                        result += ch;
                }

        }
    }
    return result;
}
