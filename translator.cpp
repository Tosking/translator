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
                if(ch == '\n')
                    state = Normal;
                break;
            case Quote:
                if(ch == '\\')
                    state = Back_Slash;
                if(ch == '"' || ch == '\''){
                    state = Normal;
                }
                result += ch;
                break;
            case Back_Slash:
                state = Normal;
            case Normal:
                switch(ch){
                    case '/':
                        state = Slash;
                        break;
                    case '"':
                        result += ch;
                        state = Quote;
                        break;
                    case '\'':
                        result += ch;
                        state = Quote;
                        break;
                    default:
                        result += ch;
                }

        }
    }
    return result;
}
