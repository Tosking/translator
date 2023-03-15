#include "translator.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Translator::Translator(string input){
    this->input = input;
}

string Translator::delete_comments(){
    string temp = "";
    State state = Normal;
    string result = "";
    for(string::iterator it = input.begin(); it != input.end(); it++){
        switch(state){
            case Slash:
                if(*it == '*'){
                    state = Comment_Star;
                    break;
                }
                result += *it;
                state = Normal;
                break;
            case Star:
                if(*it == '/'){
                    state = Normal;
                    break;
                }
                result += *it;
                state = Normal;
                break;
            case Comment_Star:
                if(*it == '*'){
                    state = Star;
                }
                break;
            case Comment_Slash:
                if(*it == '\n'){
                    state = Normal;
                }
            case Normal:
                switch(*it){
                    case '/':
                        state = Slash;
                        break;
                    case '*':
                        state = Star;
                        break;
                    default:
                        result += *it;
                }

        }
    }
    return result;
}
