#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_
#include <string>
using namespace std;
enum State {
Normal,
Slash,
Star,
Comment_Slash,
Comment_Star,
OQuote,
TQuote,
OBack_Slash,
TBack_Slash,
Number,
Identifer,
Skip,
Double,
Dot,
Long,

};
class Translator{
private:
    string input;

public:
    string delete_comments();
    string
    Translator(string input);
};

#endif // TRANSLATOR_H_
       //
       //
if(!isalpha(c) && !isidigt(c))
{
    /**/
    states = CheckSymbol(c);
    break;
}
static const State CheckSymbol(char &c)
{
    switch(c)
    {

        case '/':
            return State::Slash;
        case '\'':
            return State::OQuote;
    }
}
