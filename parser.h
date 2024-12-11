#include "scanner.h"


class Parser
{
private:
    Scanner *scanner;
    Token *lToken;

    void advance();
    void match(int);

public:
    Parser(string);
    void run();
    void program();
   
    void function();
    void type();
    void paramTypes();
    void varDeclaration();
    void statement();
    void assign();
    void expression();
    void expressionPrime();
    void prefixExpression();

    void error(string);
    bool _isType();
    bool _isStatement();
    bool _isExpression();
    bool _isAssign();
};