#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1000

int main() {
    char *input_filename = "ctest.txt";  // name of input file
    FILE *input_file = fopen(input_filename, "r");  // open file in read mode

    if (input_file == NULL) {
        printf("Error: could not open file %s\n", input_filename);
        return 1;
    }

    char input_buffer[MAX_INPUT_SIZE];  // buffer to store input
    int pos = 0;  // position in buffer

    // read input file until end of file or buffer size is reached
    int c;
    while ((c = fgetc(input_file)) != EOF && pos < MAX_INPUT_SIZE - 1) {
        input_buffer[pos++] = c;
    }

    input_buffer[pos] = '\0';  // null-terminate buffer

    fclose(input_file);  // close file

    printf("Input string: %s\n", input_buffer);

    return 0;
}
