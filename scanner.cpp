#include "scanner.h"

//Constructor that receives a string with the name of the input file
//and fills input with its contents.
Scanner::Scanner(string input)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos  = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else
        cout << "Unable to open file\n";
}

int Scanner::getLine()
{
    return line;
}
Token *
Scanner::nextToken()
{
    Token *tok;
    string lexeme;

    // 10. Whitespace should be ignored.
    if (isspace(input[pos]))
    {
        while (isspace(input[pos]))
        {
            if (input[pos] == '\n')
                line++;
            pos++;
        }
        tok = new Token(SPACE);
    }

    // 9 Comments should be ignored. They follow the C format and can be inline or block.
    else if (input[pos] == '/')
    {
        // Inline comments begin with the characters // and end with a newline
        if (input[pos + 1] == '/')
        {
            while (input[pos] != '\n')
                pos++;
            line++;
            pos++;
            tok = new Token(COMMENT);
        }

        // Block comments are delimited by /* and */
        else if (input[pos + 1] == '*')
        {
            while (input[pos] != '*' || input[pos + 1] != '/')
            {
                if (input[pos] == '\n')
                    line++;
                pos++;
            }
            pos += 2;
            tok = new Token(COMMENT);
        }
    }

    // 8. Separadores
    else if (input[pos] == '(')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == ')')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == '{')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == '}')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == '[')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == ']')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == ',')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }
    else if (input[pos] == ';')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(SEPARATORS, lexeme);
    }

    // 7. Operadores
    else if (input[pos] == '+')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '-')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '*')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '/')
    {
        lexeme += input[pos];
        pos++;
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '=')
    {
        lexeme += input[pos];
        pos++;
        if (input[pos] == '=')
        {
            lexeme += input[pos];
            pos++;
        }

        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '!')
    {
        lexeme += input[pos];
        pos++;

        if (input[pos] == '=')
        {
            lexeme += input[pos];
            pos++;
        }

        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '<')
    {
        lexeme += input[pos];
        pos++;
        if (input[pos] == '=')
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '>')
    {
        lexeme += input[pos];
        pos++;
        if (input[pos] == '=')
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '&')
    {
        lexeme += input[pos];
        pos++;
        if (input[pos] == '&')
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(OPERATOR, lexeme);
    }
    else if (input[pos] == '|')
    {
        lexeme += input[pos];
        pos++;
        if (input[pos] == '|')
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(OPERATOR, lexeme);
    }

   // 4. integerconstant → digit+
    else if (isdigit(input[pos]))
    {
        lexeme += input[pos];
        pos++;
        while (isdigit(input[pos]))
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(INTEGER_CONSTANT, lexeme);
    }

    // 12. Reserved word: void
    else if (input[pos] == 'v' && input[pos + 1] == 'o' && input[pos + 2] == 'i' && input[pos + 3] == 'd')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12. Reserved word: char
    else if (input[pos] == 'c' && input[pos + 1] == 'h' && input[pos + 2] == 'a' && input[pos + 3] == 'r')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12.  Reserved word: int
    else if (input[pos] == 'i' && input[pos + 1] == 'n' && input[pos + 2] == 't')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12. Reserved word: if
    else if (input[pos] == 'i' && input[pos + 1] == 'f')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12.  Reserved word: else
    else if (input[pos] == 'e' && input[pos + 1] == 'l' && input[pos + 2] == 's' && input[pos + 3] == 'e')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12.  Reserved word: while
    else if (input[pos] == 'w' && input[pos + 1] == 'h' && input[pos + 2] == 'i' && input[pos + 3] == 'l' && input[pos + 4] == 'e')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12.  Reserved word: for
    else if (input[pos] == 'f' && input[pos + 1] == 'o' && input[pos + 2] == 'r')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }  // 12.  Reserved word: return
    else if (input[pos] == 'r' && input[pos + 1] == 'e' && input[pos + 2] == 't' && input[pos + 3] == 'u' && input[pos + 4] == 'r' && input[pos + 5] == 'n')
    {
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        lexeme += input[pos];
        pos++;
        tok = new Token(RESERVADED, lexeme);
    }

    // 5. charconstant → ‘ch’ | ‘\n’ | ‘\0’, where ch is any printable ASCII character.
    else if (input[pos] == '\'')
    {
        lexeme += input[pos];
        pos++;

        // \n ou \0
        if (input[pos] == '\\') // \n ou \0
        {
            lexeme += input[pos];
            pos++;
            if (input[pos] == 'n' || input[pos] == '0') 
            {
                lexeme += input[pos];
                pos++;
            }
            else
            {
                lexicalError("Caractere inválido");
            }
        }

        // ch
        else if (isprint(input[pos]) && input[pos] != '\'') // ch
        {
            lexeme += input[pos];
            pos++;
        }
        else
        {
            lexicalError("Caractere inválido");
        }
        if (input[pos] == '\'') 
        {
            lexeme += input[pos];
            pos++;
            tok = new Token(CHAR_CONSTANT, lexeme);
        }
        else
        {
            lexicalError("Caractere inválido");
        }
    }

    //6. stringconstant → “(ch)*”, where ch is any printable ASCII character.
    else if (input[pos] == '\"')
    {
        lexeme += input[pos];
        pos++;
        while (isprint(input[pos]) && input[pos] != '\"' && input[pos] != '\n')
        {
            lexeme += input[pos];
            pos++;
        }
        if (input[pos] == '\"')
        {
            lexeme += input[pos];
            pos++;
            tok = new Token(STRING_CONSTANT, lexeme);
        }
        else
        {
            lexicalError("String inválida");
        }
    }

    // 3. ID → letter (letter | digit | _ )∗
    else if (isalpha(input[pos]) || input[pos] == '_')
    {
        lexeme += input[pos];
        pos++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            lexeme += input[pos];
            pos++;
        }
        tok = new Token(ID, lexeme);
    }

    // 12. EOF
    else if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }
    return tok;
}

void Scanner::lexicalError(string msg)
{
    cout << "Lexical error: " << msg << " at line " << line << endl;

    exit(EXIT_FAILURE);
}
