#include <fstream>
#include "token.h"

class Scanner 
{
    private: 
        string input; //Store the input text
        int pos;      //Current position
        int line;
    
    public:
        //Construtor
        Scanner(string);

        int getLine();
    
        //Method that returns the next token from the input
        Token* nextToken();        
    
        //Method to handle errors
        void lexicalError(string);
};
