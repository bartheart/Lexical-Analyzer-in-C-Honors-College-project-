//Author: Bemnet Mekrebu
//Course: CSCE 3600
//EUID: 11602811

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //standard C library

#define STRING_LENGTH 100


//Define tokens 
enum TokenType{
    IDENTIFIER =1,
    INTEGER_LITERAL,
    STRING_LITERAL,
    OPERATOR,
    IF, ELSE, WHILE, FOR,
    SEMICOLON, COMMA, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
    LEFT_BRACE, RIGHT_BRACE
    
};

//Define regular expressions for the tokens
#define REG_IDENTIFIER "[a-zA-Z_][a-zA-Z0-9]*"
#define REG_INTEGER_LI "[0-9]+"
#define REG_STRING_LI "\"[^\"]*\""
#define REG_OPERATOR "[+\\-*/]|==|!=|<=|>=|<|>" //% is not included
#define REG_IF "if"
#define REG_ELSE "else"
#define REG_WHILE "while"
#define REG_FOR "for"
#define REG_SEMICOLON ";"
#define REG_COMMA ","
#define REG_LEFT_PARANTHESIS "\\("
#define REG_RIGHT_PARANTHESIS "\\)"
#define REG_LEFT_BRACE "\\{"
#define REG_RIGHT_BRACE "\\}"


//Define structure of a token
struct Token{
    enum TokenType type;
    char value[STRING_LENGTH];
};

//Funtion to match identifier token
struct Token match_identifier(char *input){
    int i = 0 ;
    while(isalpha(input[i])|| isdigit(input[i])||input[i]== '_'){
        i++;
    }
    if(i == 0){
        printf("Invalid identifier");
    }

    struct Token token;
    token.type = IDENTIFIER;
    strncpy(token.value, input, i);
    token.value[i] = '\0';
    return token;
}

struct Token match_interger_literal(char *input){
    int i = 0;
    while(isdigit(input[i])){
        i++;
    }
    if(i == 0){
        printf("Invalid integer literal");
    }

    struct Token token;
    token.type = INTEGER_LITERAL;
    strncpy(token.value, input, i);
    token.value[i] = '\0';
    return token;

}

struct Token match_operator(char *input){
    int i = 0;
    //Have to check 2 or 1 char operators

    //Match 2 char opr
    if(strncmp(input, "==", 2)== 0||strncmp(input, "!=", 2)== 0||strncmp(input, "<=", 2)== 0||strncmp(input, ">=", 2)== 0){

        struct Token token;
        token.type = OPERATOR;
        strncpy(token.value, input, 2);
        token.value[2] = '\0';
        return token;
    }
    //Match single char opr
    else{
        struct Token token;
        token.type = OPERATOR;
        token.value[0] = input[0];
        token.value[1] = '\0';
        return token;
    }

    
}

//search char function
char* strchr(const char* str, int c){
    while (*str != '\0'){
        if (*str == (char) c){
            //retrun type casted into a pointer
            return (char*) str;
        }
        str++;
    }
    return NULL;
}

//evaluate a token function
//takes a pointer to the string and delim pointing to the delimiters 
char *toekenize(char *str, const char *delim){
    static char *next_token = NULL;
    char *token = NULL;

    //reset position if new string detected
    if(str != NULL){
        next_token = str;
    }

    //next occurrence of a delimiter
    char *delimiter = strchr(next_token, delim[0]);

    //if delimiter is found, insert null cahracters
    if(delimiter != NULL){
        *delimiter = '\0';
        token = next_token;
        next_token = delimiter + 1;
    }
    //if delimiter not found countinues to the end of string
    else if(*next_token != '\0'){
        token = next_token;
        next_token += strlen(next_token);
    }

    return token;


}


//main lexer function
/* break down the input source code
- might need a symnol table to track identifiers and data types
- implement a fintie state machine 
    - determine appropriate token to asssign to each substring of the input string
    - current char, prev state, next state
    - if curr state - accept -> add token on array
- tokenize function (takes a char pointer to the input string)
    -retruns array of tokens*/
int main(){
    char input[STRING_LENGTH];
    printf("Enter a simple expression: ");
    //need to construct input buffer instead of using fgets and converting 
    //---input in to chars in an array
    fgets(input, STRING_LENGTH, stdin);

    //tokenize input
    char* token = toekenize(input, " \n");//delimiter is string of delimiters
    //tokenize a simple arthimetic expression -> then scaleup
    while (token != NULL){
        struct Token t;
        if(isdigit(token[0])){
            t = match_interger_literal(token);
        }
        else if(strchr("+-*/", token[0])){
            t = match_operator(token);
        }
        else{
            printf("invalid token:%s\n, token");
        }

        //token process
        //print token type and value 
        printf("Token type: %d, value: %s\n", t.type, t.value);

        //next token
        token = toekenize(NULL,"\n");
    }
    
}
/*
example:
void lex(char* input) {
    int i = 0;
    int state = 0;
    char buffer[STRING_LENGTH];

    while (input[i]) {
        switch (state) {
            case 0: // Initial state
                if (isalpha(input[i]) || input[i] == '_') {
                    state = 1;
                    buffer[0] = input[i];
                    i++;
                } else if (isdigit(input[i])) {
                    state = 2;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '\"') {
                    state = 3;
                    i++;
                } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                    state = 4;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '=') {
                    state = 5;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '!') {
                    state = 6;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '<' || input[i] == '>') {
                    state = 7;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '(') {
                    state = 8;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == ')') {
                    state = 9;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '{') {
                    state = 10;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == '}') {
                    state = 11;
                    buffer[0] = input[i];
                    i++;
                } else if (input[i] == ';') {
                    state = 12;
                    buffer[0] = input




without input buffer 
//Function to get the next token using a finite state machine
struct Token lexer(char *input){
    int state = 0;
    int i = 0;
    int input_length = strlen(input);
    struct Token token;
    token.type = 0;
    token.value[0] = '\0';

    while(i < input_length){
        switch(state){
            case 0:
                if(isalpha(input[i])|| input[i] == '_'){
                    state = 1;
                }
                else if(isdigit(input[i])){
                    state = 2;
                }
                else if(input[i] == '"'){
                    state = 3;
                }
                else if(strchr("+-*!<>=", input[i]) != NULL){
                    state = 4;
                }
                else if(strncmp(input+i, "if", 2) == 0 && !isalnum(input[i+2])){
                    state = 5;
                }
                else if(strncmp(input+i, "else", 4) == 0 && !isalnum(input[i+4])){
                    state = 6;
                }
                else if(strncmp(input+i, "while", 5) == 0 && !isalnum(input[i+5])){
                    state = 7;
                }
                else if(strncmp(input+i, "for", 3) == 0 && !isalnum(input[i+3])){
                    state = 8;
                }
                else if(input[i] == ';'){
                    state = 9;
                }
                else if(input[i] == ','){
                    state = 10;
                }
                else if(input[i] == '('){
                    state = 11;
                }
                else if(input[i] == ')'){
                    state = 12;
                }
                else if(input[i] == '{'){
                    state = 13;
                }
                else if(input[i] == '}'){
                    state = 14;
                }
                else{
                    printf("Invalid input character: %c", input[i]);
                    exit(1);
                }
                i++;
                break;
            case 1:
                if(isalnum(input[i]) || input[i] == '_'){
                    i++;
                }
                else{
                    token = match_identifier(input);
                    state = 0;
                }
                break;
            case 2:
                if(isdigit(input[i])){
                    i++;
                }
                else{
                    token = match_interger_literal(input);
                    state = 0;
                }
                break;
            case 3:
                i++;
                while(input[i] != '"' && input[i] != '\0'){
                    i++;
                }
                if(input[i] == '\0'){
                    printf("Unterminated string literal");
                    exit(1);
                }
                else{
                    i++;
                    token.type = STRING_LITERAL;
                    strncpy(token.value, input, i);
                    token.value[i] = '\0';
                    state = 0;
                }
                break;
            case 4:
                token = match_operator(input+i);
                state = 0;
                break;
            case 5:
                token.type = IF;
                strcpy(token.value, "if");
                i += 2;
                state = 0;
                break;
            case 6:
                token.type = ELSE;
                strcpy(token.value, "else");
                i += 4;
                state = 0;
                break;
            case 7:
                token.type = WHILE;
                strcpy(token.value, "while");
                i += 5;
                state = 0;
                break;
            case 8:
                token.type = FOR;
                strcpy(token.value, "for


*/


//Build input buffer
/*Building an input lexer is important in storing series of input temprorarily from a file or text
- avoid to repeatedly acess the file
- pre-process input such as removing comments
- out put debugging info from the buffer (informative errrors)
*/

//Build tokenizer
/*already started this phase
- have to integrate it with the input buffer */

//Build White space and comment handler

//Build error handler

//Build output generator 

//Final integration module 