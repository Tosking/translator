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
                if(ch == '/'){
                    state = Comment_Slash;
                    break;
                }
                else{
                    result += '/';
                    result += ch;
                    state = Normal;
                }
                break;
            case Star:
                if(ch == '/'){
                    state = Normal;
                    result += ' ';
                    break;
                }
                else if(ch == '*')
                    break;
                state = Comment_Star;
                break;
            case Comment_Star:
                if(ch == '*')
                    state = Star;
                break;
            case Comment_Slash:
                if(ch == '\n'){
                    state = Normal;
                    result += '\n';
                }
                break;
            case OBack_Slash:
                state = OQuote;
                result += ch;
                break;
            case TBack_Slash:
                state = TQuote;
                result += ch;
                break;
            case TQuote:
                if(ch == '\\')
                    state = TBack_Slash;
                if(ch == '"'){
                    state = Normal;
                }
                result += ch;
                break;
            case OQuote:
                if(ch == '\\')
                    state = OBack_Slash;
                if(ch == '\''){
                    state = Normal;
                }
                result += ch;
                break;
            case Normal:
                switch(ch){
                    case '/':
                        state = Slash;
                        break;
                    case '"':
                        result += ch;
                        state = TQuote;
                        break;
                    case '\'':
                        result += ch;
                        state = OQuote;
                        break;
                    default:
                        result += ch;
                }

        }
    }
    return result;
}
