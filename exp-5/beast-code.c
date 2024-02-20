#include <stdio.h>

#ifndef MAX_SIZE
#define MAX_SIZE 1000
#endif

int remove_comments_and_whitespaces(FILE *input_file, FILE *output_file) {
  char curr, next;

  // while current char is not EOF
  while ((curr = fgetc(input_file)) != EOF) {
    // comments //
    // comment start symbol '/'
    if (curr == '/') {
      next = fgetc(input_file);

      // TODO: 1. remove inline comments: //
      if (next == '/') {
        // ignore the rest of the line
        while ((curr = fgetc(input_file)) != '\n' && curr != EOF) {
          // inside single-line comment
        }

        // put back the new line for inline comment
        if (curr == '\n') {
          fputc(curr, output_file);
        }
      }

      // TODO: 2. remove multiline comments: /**/
      else if (next == '*') {
        // ignore until closing tokens (*/)
        while (!((curr = fgetc(input_file)) == '*' && (next = fgetc(input_file)) == '/')) {
          // inside multi-line comment
          // check if EOF
          if (curr == EOF) {
            puts("Error: Unclosed multiline comment.");
            return 1;
          }
        }
      }

      // write both current and next character to the output file
      else {
        fputc(curr, output_file);
        fputc(next, output_file);
      }
    }

    // whitespaces //
    else if (curr == '\n') {
      // ignore all subsequent new lines
      while (((next = fgetc(input_file)) == '\n') && next != EOF) {
      };

      fputc(curr, output_file);

      if (next != EOF) {
        fputc(next, output_file);
      }
    }

    else {
      fputc(curr, output_file);
    }
  }
}

int main() {
  char input_file_name[MAX_SIZE] = "sample.txt";
  char output_file_name[MAX_SIZE] = "out.c";

  //   printf("Name of the input file:");
  //   scanf("%s", input_file_name);
  //   printf("Name of the output file:");
  //   scanf("%s", output_file_name);

  FILE *in_file = fopen(input_file_name, "r");

  if (in_file == NULL) {
    puts("Error: Unable to open input file.");
    return 1;
  }

  FILE *out_file = fopen(output_file_name, "w");

  if (out_file == NULL) {
    puts("Error: Unable to open output file.");
    return 1;
  }

  // function to remove comments and whitespaces
  remove_comments_and_whitespaces(in_file, out_file);

  fclose(in_file);
  fclose(out_file);

  printf("Comments and whitespaces removed. Output written to %s\n", output_file_name);

  return 0;
}