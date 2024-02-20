#include <stdio.h>

int main() {
  FILE *inputFile = fopen("out.c", "r");
  FILE *outputFile = fopen("output.c", "w");
  if (inputFile == NULL || outputFile == NULL) {
    printf("Unable to open the file.\n");
    return 1;
  }

  char currentChar;
  while ((currentChar = fgetc(inputFile)) != EOF) {
    if (currentChar != ' ' && currentChar != '\t' && currentChar != '\n') {
      fputc(currentChar, outputFile);
    }
  }

  fclose(inputFile);
  fclose(outputFile);
  return 0;
}