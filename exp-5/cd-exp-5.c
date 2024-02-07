#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void remove_comments_and_whitespace(FILE *input_file, FILE *output_file) {
  bool in_comment = false;
  int prev_char = '\0';
  int current_char;

  while ((current_char = fgetc(input_file)) != EOF) {
    if (in_comment) {
      if (prev_char == '*' && current_char == '/') {
        in_comment = false;
      }
    } else {
      if (prev_char == '/' && current_char == '*') {
        in_comment = true;
      } else if (current_char == '/' && prev_char == '/') {
        // skip single-line comments
        while ((current_char = fgetc(input_file)) != '\n' && current_char != EOF) {
        }
        // end of file
        if (current_char == EOF) {
          break;
        }
      } else if (!isspace(prev_char) || !isspace(current_char)) {
        // write character to output if not in comment and not whitespace
        fputc(current_char, output_file);
      }
    }
    prev_char = current_char;
  }
}

int main() {
  char input_file_name[MAX_SIZE];
  char output_file_name[MAX_SIZE];

  printf("Enter the name of the input C source file: ");
  scanf("%s", input_file_name);
  printf("Enter the name of the output file: ");
  scanf("%s", output_file_name);

  FILE *input_file = fopen(input_file_name, "r");
  if (input_file == NULL) {
    printf("Error: Unable to open input file.\n");
    return 1;
  }

  FILE *output_file = fopen(output_file_name, "w");
  if (output_file == NULL) {
    printf("Error: Unable to open output file.\n");
    fclose(input_file);
    return 1;
  }

  remove_comments_and_whitespace(input_file, output_file);

  printf("Comments and whitespace removed. Output written to %s\n", output_file_name);

  fclose(input_file);
  fclose(output_file);

  return 0;
}
