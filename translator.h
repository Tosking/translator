#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_
#include <string>
using namespace std;
enum State {
Normal,
Slash,
Star,
Comment_Slash,
Comment_Star
};
class Translator{
private:
    string input;

public:
    string delete_comments();
    Translator(string input);
};

#endif // TRANSLATOR_H_
