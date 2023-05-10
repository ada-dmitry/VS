#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  srand(time(0));
  Stack *numbers = malloc(sizeof(Stack));
  if (numbers == NULL)
    exit(1);

  char c;
  char flag = 'f';

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      break;
    } else if (c == ' ') {
      flag = 't';
      continue;
    }

    switch (c) {
    case '0' ... '9':
      if (flag == 't') {
        numbers = add_head(numbers, (double)(c - '0'));
        flag = 'f';
      } else {
        double a = get(numbers, 0).x;
        numbers = del_head(numbers);
        a = a * 10 + c - '0';
        numbers = add_head(numbers, a);
      }
      break;

    case '+':
    case '-':
    case '*':
    case '/':
      if (len(numbers) < 2) {
        printf("Invalid expression\n");
        exit(2);
      }

      double a = get(numbers, 0).x;
      numbers = del_head(numbers);
      double b = get(numbers, 0).x;
      numbers = del_head(numbers);

      b = (c == '+') ? b + a : b;
      b = (c == '-') ? b - a : b;
      b = (c == '*') ? b * a : b;
      b = (c == '/') ? b / a : b;

      numbers = add_head(numbers, b);
      break;
    }
  }

  printf("result: %lF\n", get(numbers, -1).x);

  free(numbers);
  return 0;
}