#include <ctype.h>
#include <stdio.h>

#define MAX_SIZE 1000

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

  char currentChar, nextChar;

  while ((currentChar = fgetc(input_file)) != EOF) {
    if (currentChar == '/') {
      nextChar = fgetc(input_file);

      // single line check
      if (nextChar == '/') {
        // Ignore the rest of the line
        while ((currentChar = fgetc(input_file)) != '\n' && currentChar != EOF) {
          // this is inside inline comment
        }
      }
      // multi line comment check
      else if (nextChar == '*') {
        // Ignore until the closing */
        while (!((currentChar = fgetc(input_file)) == '*' && (nextChar = fgetc(input_file)) == '/')) {
          if (currentChar == EOF) {
            printf("Error: Unclosed multi-line comment.\n");
            return 1;
          }
        }
      } else {
        fputc(currentChar, output_file);
        fputc(nextChar, output_file);
      }
    } else {
      // write character to output if not in comment and not whitespace
      fputc(currentChar, output_file);
    }
  }

  fclose(input_file);
  fclose(output_file);

  return 0;
}