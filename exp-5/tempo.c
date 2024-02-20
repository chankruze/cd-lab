#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *inputFile = fopen("sample.txt", "r");
  FILE *outputFile1 = fopen("tempfile.tmp", "w");
  FILE *outputFile2 = fopen("o.c", "w");

  if (inputFile == NULL || outputFile1 == NULL) {
    printf("Unable to open the file.\n");
    return 1;
  }

  // Open a temporary file for writing
  if (outputFile1 == NULL) {
    printf("Error creating temporary file\n");
    fclose(inputFile);
    return 1;
  }

  // Read character by character from input file and remove single line comments and extra white spaces
  char currentChar, nextChar;
  while ((currentChar = fgetc(inputFile)) != EOF) {
    if (currentChar == '/') {
      nextChar = fgetc(inputFile);
      if (nextChar == '/') {
        // Ignore the rest of the line
        while ((currentChar = fgetc(inputFile)) != '\n' && currentChar != EOF)
          ;
      } else if (nextChar == '*') {
        // Ignore until the closing */
        while (!((currentChar = fgetc(inputFile)) == '*' && (nextChar = fgetc(inputFile)) == '/')) {
          if (currentChar == EOF) {
            printf("Error: Unclosed multi-line comment.\n");
            return 1;
          }
        }
      } else {
        fputc(currentChar, outputFile1);
        fputc(nextChar, outputFile1);
      }
    } else {
      fputc(currentChar, outputFile1);
    }
  }

  fclose(inputFile);
  fclose(outputFile1);

  inputFile = fopen("tempfile.tmp", "r");

  // Open the modified file for reading and print its contents
  char newChar, prev = NULL;
  while ((newChar = fgetc(inputFile)) != EOF) {
    if (newChar == ' ') {
      prev = newChar;
    }

    if (prev == ' ' && newChar != ' ' && newChar != '\t' && newChar != '\n') {
      fputc(prev, outputFile2);
      fputc(newChar, outputFile2);
    }
  }

  fclose(inputFile);
  fclose(outputFile2);
  return 0;
}