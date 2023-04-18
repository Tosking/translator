#include "translator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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
            case Number:
               if(!isdigit(ch)){
                   if(ch == '.')
                       state = Dot;
                   else if(ch == 'e'){
                       state = Power;
                   }
                   else if(ch == '\n'){
                       result += " ERROR!\n";
                       state = Normal;
                       break;
                   }
                   else{
                       state = Skip;
                       break;
                   }
               }
               result += ch;
               break;
            case Dot:
                if(!isdigit(ch)){
                    if(ch == 'e'){
                        state = E;
                        result += ch;
                        break;
                    }
                    else if(ch == '\n'){
                        result += " double\n";
                        state = Normal;
                        break;
                    }
                    result += ch;
                    state = Skip;
                    break;
                }
                result += ch;
                state = Double;
                break;
            case Double:
                if(!isdigit(ch)){
                    switch(ch){
                        case 'l':
                            state = Long;
                            break;
                        case '\n':
                            result += " double";
                            state = Normal;
                            break;
                        case '/':
                            result +=  " double";
                            state = Slash;
                            break;
                        case 'e':
                            state = E;
                            break;
                        default:
                            state = Skip;
                            break;
                    }
                    result += ch;
                }
                break;
            case Skip:
                if(ch == '\n'){
                    result += " ERROR!\n";
                    state = Normal;
                    break;
                }
                result += ch;
                break;
            case Long:
                result += " long\n";
                state = Normal;
                break;
            case Identifer:
                if(ch == '\n'){
                    state = Normal;
                    result += ch;
                    break;
                }
                if(!isalpha(ch)){
                    state = Skip;
                    result += ch;
                    break;
                }
            case E:
                if(!isdigit(ch)){
                    if(ch == '+' || ch == '-'){
                        state = Power;
                    }
                    else{
                        if(ch == '\n'){
                            result += " ERROR!\n";
                            state = Normal;
                            break;
                        }
                        state = Skip;
                        result += ch;
                        break;
                    }
                }
                state = Power;
                result += ch;
                break;
            case Power:
                if(!isdigit(ch)){
                    if(ch == 'l'){
                        state = Long;
                        result += ch;
                        break;
                    }
                    else if(ch == '\n'){
                        result += " double\n";
                        state = Normal;
                        break;
                    }
                    else{
                        state = Skip;
                        break;
                    }
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
                    case '.':
                        state = Dot;
                        result += ch;
                        break;
                    default:
                        if(isdigit(ch)){
                            state = Number;
                        }
                        if(isalpha(ch) || ch == '_'){
                           state = Identifer;
                        }
                        result += ch;
                        break;
                }

        }
    }
    return result;
}
