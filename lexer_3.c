//Author: Bemnet Mekrebu
//Course: CSCE 3600
//EUID: 11602811

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //standard C library
#include <stdarg.h>


#define MAX_INPUT_SIZE 1000 

//input buffer
char input_buffer[MAX_INPUT_SIZE];


//Define tokens 
enum TokenType{
    IDENTIFIER =1,
    KEYWORD,
    CONSTANT,
    STRING_LITERAL,
    PUNCTUATOR
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

//comment handling

//index postion 
static int pos = 0, line = 0, col = 0;
static char curr_char = ' ';

// Open the input file and read its contents into the input buffer
void open_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        error(0, 0, "cannot open file: %s", filename);
    }
    size_t len = fread(input_buffer, sizeof(char), MAX_INPUT_SIZE, fp);
    if (len >= MAX_INPUT_SIZE) {
        error(0, 0, "input too large, max size is %d", MAX_INPUT_SIZE);
    }
    input_buffer[len] = '\0';
    fclose(fp);
}

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
        char *arr[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic _Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
        //extract number of keywords
        int num_keywords = sizeof(arr) / sizeof(char*);

        for (int i = 0; i<num_keywords; i++){
            if (strcmp(identifier, arr[i]) == 0){
                token.type = KEYWORD;
                token.text = strdup(identifier);
                break;
            }
        }
        //fall back if its not a keyword
        if (token.type != KEYWORD){
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
        token.type = CONSTANT;
        token.text = "INTEGER_CONSTANT";
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
        case '+': token.type = PUNCTUATOR; token.text = "ADD"; next_character(); break;
        case '-': token.type = PUNCTUATOR; token.text = "SUB"; next_character(); break;
        case '*': token.type = PUNCTUATOR; token.text = "MUL"; next_character(); break;
        case '/': token.type = PUNCTUATOR; token.text = "DIV"; next_character(); break;
        case '%': token.type = PUNCTUATOR; token.text = "MOD"; next_character(); break;
        case ';': token.type = PUNCTUATOR; token.text = "SEMICOLON"; next_character(); break;
        case ',': token.type = PUNCTUATOR; token.text = "COMMA"; next_character(); break;
        case '(': token.type = PUNCTUATOR; token.text = "LEFT_PARENTHESIS"; next_character(); break;
        case ')': token.type = PUNCTUATOR; token.text = "RIGHT_PARENTHESIS"; next_character(); break;
        case '{': token.type = PUNCTUATOR; token.text = "LEFT_BRACE"; next_character(); break;
        case '}': token.type = PUNCTUATOR; token.text = "RIGHT_BRACE"; next_character(); break;
        default: error(line, col, "Invalid character '%c'", curr_char);
    }

    return token;
}


int main(){
    
    //printf("Enter a simple expression: ");

    //fgets(input_buffer, sizeof(input_buffer), stdin);

    // Open input file
    FILE *input_file = fopen("test.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file");
        return 1;
    }

    //lexer call
    struct Token token;
    while ((token = lex()).type != EOF){
        switch (token.type){
            case IDENTIFIER:
                printf("IDENTIFIER: %s\n", token.text);
                free(token.text);
                break;
            case KEYWORD:
                printf("KEYWORD: %s\n", token.text);
                //free(token.text);
                break;
            case CONSTANT:
                printf("CONSTANT: %d\n", token.n);
                //free(token.text);
                break;
            case STRING_LITERAL:
                printf("STRING_LITERAL: %s\n", token.text);
                free(token.text);
                break;
            case PUNCTUATOR:
                printf("PUNCTUATOR: %s\n", token.text);
                //free(token.text);
                break;
            default: error(token.errorLine, token.errorColumn, "Invalid token");
        }
    }

    fclose(input_file);
    return 0;
}