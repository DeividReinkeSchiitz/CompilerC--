#include "parser.h"


Parser::Parser(string input)
{
    scanner = new Scanner(input);
    lToken  = new Token(UNDEF);
}

void Parser::advance()
{
    lToken = scanner->nextToken();
    // ignore comments and spaces
    while (lToken->name == COMMENT || lToken->name == SPACE || lToken->name == UNDEF)
        lToken = scanner->nextToken();

    // std::cout << "Token name: " << lToken->name << std::endl;
    // std::cout << "Token lexeme: " << lToken->lexeme << std::endl;
}


void Parser::match(int t)
{
    if (lToken->name == t || lToken->attribute == t)
        advance();
    else
        error("Error: expected " + to_string(t) + ". Token founded: " + to_string(lToken->name) + ", lexeme:  " + lToken->lexeme);
}

void Parser::run()
{
    advance();
    program();
    match(END_OF_FILE);
    std::cout << "Compiled Successfull!" << std::endl;
}


/*
1. Program → (Function)∗ EOF
*/
void Parser::program()
{
    while (lToken->name != END_OF_FILE)
        function();
}

/*
2. Function → Type ID( ParamTypes ){(Type VarDeclaration(, VarDeclaration)∗;)∗
(Statement)∗}
| void ID( ParamTypes ){(Type VarDeclaration(, VarDeclaration)∗;)∗ (Statement)∗}
*/
void Parser::function()
{
    // print("FUNCTION\n");
    if (lToken->name == RESERVADED && lToken->lexeme == "void")
    {
        match(RESERVADED);  // void
        match(ID);          // ID
        match(SEPARATORS);  // (
        paramTypes();       // ParamTypes
        match(SEPARATORS);  // )
        match(SEPARATORS);  // {
        while (_isType())   // (Type VarDeclaration(, VarDeclaration)∗;)∗
        {
            type();  // Type
            varDeclaration();

            while (lToken->name == SEPARATORS && lToken->lexeme == ",")
            {
                match(SEPARATORS);  // ,
                varDeclaration();
            }
            match(SEPARATORS);  // ;
        }
        while (_isStatement())  // (Statement)∗
        {
            statement();
        }
        match(SEPARATORS);  // }
    }
    else
    {
        type();             // Type
        match(ID);          // ID
        match(SEPARATORS);  // (
        paramTypes();       // ParamTypes
        match(SEPARATORS);  // )
        match(SEPARATORS);  // {
        while (_isType())   // (Type VarDeclaration(, VarDeclaration)∗;)∗
        {
            type();  // Type
            varDeclaration();

            while (lToken->name == SEPARATORS && lToken->lexeme == ",")
            {
                match(SEPARATORS);  // ,
                varDeclaration();
            }

            match(SEPARATORS);  // ;
        }
        while (_isStatement())  // (Statement)∗
        {

            statement();
        }

        match(SEPARATORS);  // }
    }
}

/*
3. VarDeclaration → ID ([integerconstant] )?
*/
void Parser::varDeclaration()
{
    // print("VAR DECLARATION\n");
    match(ID);  // ID
    if (lToken->name == SEPARATORS && lToken->lexeme == "[")
    {
        match(SEPARATORS);        // [
        match(INTEGER_CONSTANT);  // integerconstant
        match(SEPARATORS);        // ]
    }
}

/*
4. Type → char
| int
*/
bool Parser::_isType()
{
    if (lToken->name == RESERVADED && (lToken->lexeme == "char" || lToken->lexeme == "int"))
        return true;
    return false;
}
void Parser::type()
{
    // print("TYPE\n");
    if (lToken->name == RESERVADED && lToken->lexeme == "char")
    {
        match(RESERVADED);  // char
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "int")
    {
        match(RESERVADED);  // int
    }
    else
    {
        error("Erro: experado char ou int. Token encontrado: " + to_string(lToken->name) + " - " + lToken->lexeme);
    }
}

/*
5. ParamTypes → void
| Type ID([])?(,Type ID([])?)∗
*/
void Parser::paramTypes()
{
    // print("PARAM TYPES\n");
    if (lToken->name == RESERVADED && lToken->lexeme == "void")
    {
        match(RESERVADED);  // void
    }
    else
    {
        type();     // Type
        match(ID);  // ID
        if (lToken->name == SEPARATORS && lToken->lexeme == "[")
        {
            match(SEPARATORS);  // [
            match(SEPARATORS);  // ]
        }
        while (lToken->name == SEPARATORS && lToken->lexeme == ",")
        {
            match(SEPARATORS);  // ,
            type();             // Type
            match(ID);          // ID
            if (lToken->name == SEPARATORS && lToken->lexeme == "[")
            {
                match(SEPARATORS);  // [
                match(SEPARATORS);  // ]
            }
        }
    }
}

/*
6. Statement → if ( Expression ) Statement (else Statement)?
| while ( Expression ) Statement
| for ( (Assign)?;(Expression)?;(Assign)? ) Statement
| return (Expression)?;
| Assign ;
| ID( (Expression( , Expression)∗)? );
| { (Statement)∗ }
| ;
*/
bool Parser::_isStatement()
{
    bool isStatement = false;
    if (lToken->name == RESERVADED && lToken->lexeme == "if")
    {
        isStatement = true;
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "while")
    {
        isStatement = true;
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "for")
    {
        isStatement = true;
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "return")
    {
        isStatement = true;
    }
    else if (lToken->name == ID)
    {
        isStatement = true;
    }
    else if (lToken->name == SEPARATORS && lToken->lexeme == "{")
    {
        isStatement = true;
    }
    else if (lToken->name == SEPARATORS && lToken->lexeme == ";")
    {
        isStatement = true;
    }

    return isStatement;
}

void Parser::statement()
{
    // print("STATEMENT\n");
    if (lToken->name == RESERVADED && lToken->lexeme == "if")
    {
        match(RESERVADED);  // if
        match(SEPARATORS);  // (
        expression();       // Expression
        match(SEPARATORS);  // )
        statement();        // Statement
        if (lToken->name == RESERVADED && lToken->lexeme == "else")
        {
            match(RESERVADED);  // else
            statement();        // Statement
        }
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "while")
    {
        match(RESERVADED);  // while
        match(SEPARATORS);  // (
        expression();       // Expression

        match(SEPARATORS);  // )
        statement();        // Statement
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "for")
    {
        match(RESERVADED);  // for
        match(SEPARATORS);  // (
        if (_isAssign())
        {
            match(ID);  // Assign
            assign();   // Assign
        }
        match(SEPARATORS);  // ;
        if (_isExpression())
            expression();   // Expression
        match(SEPARATORS);  // ;
        if (_isAssign())
        {
            match(ID);  // Assign
            assign();  // Assign
        }
        match(SEPARATORS);  // )
    }
    else if (lToken->name == RESERVADED && lToken->lexeme == "return")
    {
        match(RESERVADED);  // return
        if (_isExpression())
            expression();  // Expression

        match(SEPARATORS);  // ;
    }
    else if (lToken->name == ID)
    {
        match(ID);  // ID
        if (lToken->name == SEPARATORS && lToken->lexeme == "(")
        {
            match(SEPARATORS);  // (
            if (_isExpression())
            {
                expression();  // Expression
                while (lToken->name == SEPARATORS && lToken->lexeme == ",")
                {
                    match(SEPARATORS);  // ,
                    expression();       // Expression
                }
            }
            match(SEPARATORS);  // )
        }
        else
        {
            // Assign
            assign();
        }
        match(SEPARATORS);  // ;
    }
    else if (lToken->name == SEPARATORS && lToken->lexeme == "{")
    {
        match(SEPARATORS);      // {
        while (_isStatement())  // (Statement)∗
        {
            statement();
        }
        match(SEPARATORS);  // }
    }
    else if (lToken->name == SEPARATORS && lToken->lexeme == ";")
    {
        match(SEPARATORS);  // ;
    }
}

/*
7. Assign → ID ([ Expression ])? = Expression
*/
bool Parser::_isAssign()
{
    bool isAssign = false;
    if (lToken->name == ID)
        isAssign = true;

    return isAssign;
}

void Parser::assign()
{
    if (lToken->name == SEPARATORS && lToken->lexeme == "[")
    {
        match(SEPARATORS);  // [
        expression();       // Expression
        match(SEPARATORS);  // ]
    }
    match(OPERATOR);  // =
    expression();     // Expression
}

/*
Expression → PrefixExpression ExpressionPrime
ExpressionPrime → BinOp PrefixExpression ExpressionPrime
                | RelOp PrefixExpression ExpressionPrime
                | LogOp PrefixExpression ExpressionPrime
                | ε
PrefixExpression → - PrefixExpression
                  | ! PrefixExpression
                  | ID ( ( Expression (, Expression)* )? | [ Expression ] )?
                  | ( Expression )
                  | integerconstant
                    | charconstant
                    | stringconstant
*/
bool Parser::_isExpression()
{
    bool isExpression = false;

    if (lToken->name == ID)
        isExpression = true;
    else if (lToken->name == INTEGER_CONSTANT)
        isExpression = true;
    else if (lToken->name == SEPARATORS && lToken->lexeme == "(")
        isExpression = true;
    else if (lToken->name == OPERATOR && lToken->lexeme == "-")
        isExpression = true;
    else if (lToken->name == OPERATOR && lToken->lexeme == "!")
        isExpression = true;
    else if (lToken->name == CHAR_CONSTANT)
        isExpression = true;
    else if (lToken->name == STRING_CONSTANT)
        isExpression = true;

    return isExpression;
}

void Parser::expression()
{
    // print("EXPRESSION\n");
    prefixExpression();  // PrefixExpression
    expressionPrime();   // ExpressionPrime
}

void Parser::expressionPrime()
{
    // print("EXPRESSION PRIME\n");
    if (lToken->name == OPERATOR && (lToken->lexeme == "+" || lToken->lexeme == "-" || lToken->lexeme == "*" || lToken->lexeme == "/"))
    {
        match(OPERATOR);     // BinOp
        prefixExpression();  // PrefixExpression
        expressionPrime();   // ExpressionPrime
    }
    else if (lToken->name == OPERATOR && (lToken->lexeme == "==" || lToken->lexeme == "!=" || lToken->lexeme == "<=" || lToken->lexeme == "<" || lToken->lexeme == ">=" || lToken->lexeme == ">"))
    {
        match(OPERATOR);     // RelOp
        prefixExpression();  // PrefixExpression
        expressionPrime();   // ExpressionPrime
    }
    else if (lToken->name == OPERATOR && (lToken->lexeme == "&&" || lToken->lexeme == "||"))
    {
        match(OPERATOR);     // LogOp
        prefixExpression();  // PrefixExpression
        expressionPrime();   // ExpressionPrime
    }
}

void Parser::prefixExpression()
{
    // print("PREFIX EXPRESSION\n");
    if (lToken->name == OPERATOR && lToken->lexeme == "-")
    {
        match(OPERATOR);     // -
        prefixExpression();  // PrefixExpression
    }
    else if (lToken->name == OPERATOR && lToken->lexeme == "!")
    {
        match(OPERATOR);     // !
        prefixExpression();  // PrefixExpression
    }
    else if (lToken->name == ID)
    {
        match(ID);  // ID
        if (lToken->name == SEPARATORS && lToken->lexeme == "(")
        {
            match(SEPARATORS);  // (
            if (_isExpression())
            {
                expression();  // Expression
                while (lToken->name == SEPARATORS && lToken->lexeme == ",")
                {
                    match(SEPARATORS);  // ,
                    expression();       // Expression
                }
            }
            match(SEPARATORS);  // )
        }
        else if (lToken->name == SEPARATORS && lToken->lexeme == "[")
        {

            match(SEPARATORS);  // [
            expression();       // Expression
            match(SEPARATORS);  // ]
        }
    }
    else if (lToken->name == SEPARATORS && lToken->lexeme == "(")
    {
        match(SEPARATORS);  // (
        expression();       // Expression
        match(SEPARATORS);  // )
    }
    else if (lToken->name == INTEGER_CONSTANT)
    {
        match(INTEGER_CONSTANT);  // integerconstant
    }
    else if (lToken->name == CHAR_CONSTANT)
    {
        match(CHAR_CONSTANT);  // charconstant
    }
    else if (lToken->name == STRING_CONSTANT)
    {
        match(STRING_CONSTANT);  // stringconstant
    }
}

void Parser::error(string str)
{
    cout << "Line " << scanner->getLine() << ": " << str << endl;
    exit(EXIT_FAILURE);
}
