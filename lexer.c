//Author: Bemnet Mekrebu
//Course: CSCE 3600
//EUID: 11602811

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //standard C library
#include <stdarg.h>
#include <unistd.h>


#define MAX_INPUT_SIZE 100000 

//token type count 
int tokenCount[] = {0, 0, 0, 0, 0}; 

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


//index postion 
static int pos = 0, line = 0, col = 0;
static char curr_char = ' ';

//final count of token types
int analysis(int arr[]){
    char *toks[] = {"IDENTIFIER", "KEYWORD", "CONSTANT", "STRING_LITERAL", "PUNCTUATOR"}; 
    printf("\n      * Final Analysis *\n");
    printf("   Type        Count\n---------------------\n");
    for (int i = 0; i < 5; i++){
        printf("%-16s %-16d\n", toks[i], arr[i]);
    }
    return 0;
}

static int next_character (){
    if(pos >= strlen(input_buffer)){
        printf("-----------Reached end of file----------\n");
        analysis(tokenCount);
        exit(0);
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

    //Handling comments and division operator
    if (curr_char == '/') {
        next_character();
        if (curr_char == '/') {
            // single-line comment, skip until end of line
            while (curr_char != '\n' && curr_char != EOF) {
                next_character();
            }
            // call lex again to get the next token after the comment
            return lex();
        }
        else if (curr_char == '*') {
            // block comment, skip until "*/" is found
            int comment_start_line = line;
            int comment_start_col = col - 1;
            next_character(); // consume the "*"
            while (curr_char != EOF) {
                if (curr_char == '*' && next_character() == '/') {
                    next_character(); // consume the "/"
                    // call lex again to get the next token after the comment
                    return lex();
                }
                else {
                    next_character();
                }
            }
            // reached end of input before end of comment
            error(comment_start_line, comment_start_col, "Unterminated block comment");
        }
        else {
            // division operator
            token.type = PUNCTUATOR;
            token.text = "DIV";
            return token;
        }
    }

    //handling assign and equality operations
    if (curr_char == '='){
        next_character();
        if (curr_char == '='){
            //equality operation, punctuator
            token.type = PUNCTUATOR;
            token.text = "EQUAL";
            return token;
        }
        else{
            //assign tool
            token.type = PUNCTUATOR;
            token.text = "ASSIGN";
            return token;
        }
    }

    //check for operators and punctuation
    switch (curr_char){
        case '+': token.type = PUNCTUATOR; token.text = "ADD"; next_character(); 
        if (curr_char == '+'){
            token.text = "INCREMENT"; 
        } 
        break;
        case '-': token.type = PUNCTUATOR; token.text = "SUB"; next_character(); 
        if (curr_char == '-'){
            token.text = "DECREMENT"; 
        } 
        break;
        case '*': token.type = PUNCTUATOR; token.text = "MUL"; next_character(); break;
        case '%': token.type = PUNCTUATOR; token.text = "MOD"; next_character(); break;
        case '<': token.type = PUNCTUATOR; next_character();
        if (curr_char == '='){
            token.text = "LESS_THAN_OR_EQUAL"; 
        } 
        else{
            token.text = "LESS_THAN"; 
        }
        break;
        case '>': token.type = PUNCTUATOR; next_character(); 
        if (curr_char == '=')
        {
            token.text = "GREATER_THAN_OR_EQUAL"; 
        }
        else{
            token.text = "GREATER_THAN"; 
        }
        break;
        case ';': token.type = PUNCTUATOR; token.text = "SEMICOLON"; next_character(); break;
        case ',': token.type = PUNCTUATOR; token.text = "COMMA"; next_character(); break;
        case '(': token.type = PUNCTUATOR; token.text = "LEFT_PARENTHESIS"; next_character(); break;
        case ')': token.type = PUNCTUATOR; token.text = "RIGHT_PARENTHESIS"; next_character(); break;
        case '{': token.type = PUNCTUATOR; token.text = "LEFT_BRACE"; next_character(); break;
        case '}': token.type = PUNCTUATOR; token.text = "RIGHT_BRACE"; next_character(); break;
        case '.': token.type = PUNCTUATOR; token.text = "DOT"; next_character(); break;
        case '#': token.type = PUNCTUATOR; token.text = "PREPROCESSOR"; next_character(); break;
        case '_': token.type = PUNCTUATOR; token.text = "UNDERSCORE"; next_character(); break;
        case '|': token.type = PUNCTUATOR; next_character();
        //handling OR operation
        if (curr_char == '|'){
            //Not equal operation
            token.text = "OR";
        }
        else{
            error(line, col, "Invalid character '%c'", curr_char);
        }
        break;
        case '&': token.type = PUNCTUATOR; next_character();
        //handling AND and & adrress operations
        if (curr_char == '&'){
            //Not equal operation
            token.text = "AND";
        }
        else{
            //assign tool
            token.text = "ADDRESS-OF";
        }
        break;
        //handling not equal and negate
        case '!': token.type = PUNCTUATOR; next_character(); 
        if (curr_char == '='){
            //Not equal operation
            token.text = "NOT_EQUAL";
        }
        else{
            //assign tool
            token.text = "NEGATE";
        }
        break;
        case '=': token.type = PUNCTUATOR; token.text = "ASSIGN"; next_character(); break;
        default: error(line, col, "Invalid character '%c'", curr_char);
    }

    return token;
}


int main(){
    // Open input file
    FILE *input_file = fopen("test1.c", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file");
        return 1;
    }
    else{
        printf("Intiating lexical analysis ...\n");
    }
    
    // read contents of file into input buffer
    int count = fread(input_buffer, sizeof(char), MAX_INPUT_SIZE, input_file);
    
    //lexer call
    struct Token token;
    printf("Intiating lexical analysis ...\n");
    printf("Position      TokenType      Description\n------------------------------------------\n");
    while ((token = lex()).type != EOF){
        printf("[%2d, %2d ]", line, col); // use a field width of 4 for alignment
        switch (token.type){
            case IDENTIFIER:
                printf("     IDENTIFIER     %s\n", token.text);
                tokenCount[0]++; 
                free(token.text);
                break;
            case KEYWORD:
                printf("      KEYWORD       %s\n", token.text);
                tokenCount[1]++; 
                break;  
            case CONSTANT:
                printf("      CONSTANT      %d\n", token.n);
                tokenCount[2]++; 
                break;
            case STRING_LITERAL:
                printf("    STRING_LIT      %s\n", token.text);
                tokenCount[3]++; 
                free(token.text);
                break;
            case PUNCTUATOR:
                printf("    PUNCTUATOR      %s\n", token.text);
                tokenCount[4]++; 
                break;
            default: 
                error(token.errorLine, token.errorColumn, "Invalid token");
        }
    }

    return 0;
}