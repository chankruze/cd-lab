#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
  char str[MAX];

  printf("Input a string: ");

  // read and store the string
  fgets(str, MAX, stdin);
  str[strcspn(str, "\n")] = 0;

  // calculate the length
  size_t str_len = strlen(str);

  // pattern: b
  if (str_len == 1 && str[0] == 'b') {
    puts("String matches pattern (b | b*a+ | baa)");
    return 0;
  }

  // if the stirng doesn't end with a, then invalid
  if (str[str_len - 1] != 'a') {
    puts("Invalid string");
    return 0;
  }

  // pattern: b*a+ | baa
  for (size_t i = 0; i < str_len; i++) {
    if (str[i] == 'a' && str[i + 1] == 'b') {
      puts("Invalid string");
      return 0;
    }

    puts("String matches pattern (b | b*a+ | baa)");
    return 0;
  }
}