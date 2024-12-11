#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

/*
1. letters → [a-zA-Z]
2. digits → [0-9]
3. ID → letter (letter | digit | _ )∗
4. integerconstant → digit+
5. charconstant → ‘ch’ | ‘\n’ | ‘\0’, where ch is any printable ASCII character (as
specified by the isprint() function, except \ and single quotes.
6. stringconstant → “(ch)*”, where ch is any printable ASCII character
 (as specified by the isprint() function, except double quotes and \n .
7. Operadores → + | - | * | / | = | == | != | <= | < | >= | > | && | || | !
8. Separadores → ( | ) | { | } | [ | ] | , | ;
9. Comments should be ignored. They follow the C format and can be inline or block. 
Inline comments begin with the characters // and end with a newline, while block
comments are delimited by /* and * /.
10.Whitespace should be ignored.
11. Reserved words: void, char, int, if, else, while, for, return
12. The end of the file is represented by EOF.
*/

enum Names 
{
    UNDEF = 0,
    LETTER = 1,
    DIGIT = 2,
    ID = 3,
    INTEGER_CONSTANT = 4,
    CHAR_CONSTANT = 5,
    STRING_CONSTANT = 6,
    OPERATOR = 7,
    SEPARATORS   = 8,
    COMMENT = 9,
    SPACE = 10,
    RESERVADED = 11,
    END_OF_FILE
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};
