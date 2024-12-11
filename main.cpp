#include "parser.h"
// To run this code, you need to compile it with the following command:
// g++ -o compiler principal.cpp scanner.cpp

int main(int argc, char *argv[])
{
    // Verify if the user has passed the file name as an argument
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.cmm\n";
        return 1;
    }

    // Create a new parser
    Parser *parser = new Parser(argv[1]);

    // Run the parser
    parser->run();

    return 0;
}