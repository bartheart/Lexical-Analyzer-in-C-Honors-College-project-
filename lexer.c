//Author: Bemnet Mekrebu
//Course: CSCE 3600
//EUID: 11602811

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //standard C library


#define MAX_INPUT_SIZE 100 

//input buffer
char input_buffer[MAX_INPUT_SIZE];


//Define tokens 
enum TokenType{
    IDENTIFIER =1,
    INTEGER_LITERAL,
    STRING_LITERAL,
    ADD, SUB, NEGATE, DIV, MOD, MUL, 
    IF, ELSE, WHILE, FOR,
    SEMICOLON, COMMA, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
    LEFT_BRACE, RIGHT_BRACE
    
};

//Define structure of a token
struct Token{
    enum TokenType type;             //store token type
    int errorLine, errorColumn;      //store error for the pareser and debugging
    union {
        int n;                       // store value of constants
        char *text;                  //store text of identifiers
    };
};

//Error handling
void error(int line, int col, const char *msg, ...){
    //varaible no of arguements
    va_list args;
    va_start(args, msg);
    printf("(%d, %d) error: ", line, col);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
    exit(1);

}

//index postion 
static int pos = 0, line = 0, col = 0;
static char curr_char = ' ';
static int next_character (){
    if(pos >= strlen(input_buffer)){
        return EOF;
    }
    curr_char = input_buffer[pos++];
    ++col;

    if (curr_char == '\n') {
        ++line;
        col = 0;
    }

    return curr_char;
}

//lex function
struct Token lex(){
    struct Token token = {0};

    //skip whitespace
    while (isspace(curr_char)){
        next_character();
    }

    //check for end of input
    if (curr_char == EOF){
        token.type = EOF;
        return token;
    }

    //check for identifier or keyword
    if (isalpha(curr_char)){
        int len = 0;
        char identifier[MAX_INPUT_SIZE];

        //read identifier
        while (isalnum(curr_char) || curr_char == '_'){
            identifier[len++] = curr_char;
            next_character();
        }
        identifier[len] = '\0';

        //check for keyword
        if (strcmp(identifier, "if") == 0){
            token.type = IF;
        } else if (strcmp(identifier, "else") == 0){
            token.type = ELSE;
        } else if (strcmp(identifier, "while") == 0){
            token.type = WHILE;
        } else if (strcmp(identifier, "for") == 0){
            token.type = FOR;
        } else {
            //identifier
            token.type = IDENTIFIER;
            token.text = strdup(identifier);
        }
        return token;
    }

    //check for number
    if (isdigit(curr_char)){
        int value = 0;
        while (isdigit(curr_char)){
            value = value * 10 + curr_char - '0';
            next_character();
        }
        token.type = INTEGER_LITERAL;
        token.n = value;
        return token;
    }

    //check for string literal
    if (curr_char == '\"'){
        int len = 0;
        char text[MAX_INPUT_SIZE];

        //read string literal
        next_character();
        while (curr_char != '\"'){
            if (curr_char == '\\'){
                next_character();
            }
            text[len++] = curr_char;
            next_character();
        }
        text[len] = '\0';

        token.type = STRING_LITERAL;
        token.text = strdup(text);
        next_character();
        return token;
    }

    //check for operators and punctuation
    switch (curr_char){
        case '+': token.type = ADD; next_character(); break;
        case '-': token.type = SUB; next_character(); break;
        case '*': token.type = MUL; next_character(); break;
        case '/': token.type = DIV; next_character(); break;
        case '%': token.type = MOD; next_character(); break;
        case ';': token.type = SEMICOLON; next_character(); break;
        case ',': token.type = COMMA; next_character(); break;
        case '(': token.type = LEFT_PARENTHESIS; next_character(); break;
        case ')': token.type = RIGHT_PARENTHESIS; next_character(); break;
        case '{': token.type = LEFT_BRACE; next_character(); break;
        case '}': token.type = RIGHT_BRACE; next_character(); break;
        default: error(line, col, "Invalid character '%c'", curr_char);
    }

    return token;
}


int main(){
    printf("Enter a simple expression: ");

    fgets(input_buffer, sizeof(input_buffer), stdin);

    //lexer call
    struct Token token;
    while ((token = lex()).type != EOF){
        switch (token.type){
            case IDENTIFIER:
                printf("IDENTIFIER: %s\n", token.text);
                free(token.text);
                break;
            case INTEGER_LITERAL:
                printf("INTEGER_LITERAL: %d\n", token.n);
                break;
            case STRING_LITERAL:
                printf("STRING_LITERAL: %s\n", token.text);
                free(token.text);
                break;
            case ADD: printf("ADD\n"); break;
            case SUB: printf("SUB\n"); break;
            case MUL: printf("MUL\n"); break;
            case DIV: printf("DIV\n"); break;
            case MOD: printf("MOD\n"); break;
            case IF: printf("IF\n"); break;
            case ELSE: printf("ELSE\n"); break;
            case WHILE: printf("WHILE\n"); break;
            case FOR: printf("FOR\n"); break;
            case SEMICOLON: printf("SEMICOLON\n"); break;
            case COMMA: printf("COMMA\n"); break;
            case LEFT_PARENTHESIS: printf("LEFT_PARENTHESIS\n"); break;
            case RIGHT_PARENTHESIS: printf("RIGHT_PARENTHESIS\n"); break;
            case LEFT_BRACE: printf("LEFT_BRACE\n"); break;
            case RIGHT_BRACE: printf("RIGHT_BRACE\n"); break;
            default: error(token.errorLine, token.errorColumn, "Invalid token");
        }
    }

    return 0;
}