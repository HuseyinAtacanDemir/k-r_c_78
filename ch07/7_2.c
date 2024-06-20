#include <stdio.h>
#include "7_2_helpers.h"

main()
{
  double num, op2;
  int test;

  while((test = scanf("%lf", &num)) != EOF) {
    if (test == 0) {
      char c = '\0'; 
      scanf("%c", &c);
      switch (c) {
        case '+':
          push(pop() + pop());
          break;
        case '*':
          push(pop() * pop());
          break;
        case '-':
          op2 = pop();
          push(pop() - op2);
          break;
        case '/':
          op2 = pop();
          if (op2 != 0.0)
            push(pop() / op2);
          else
            printf("Divide By Zero\n");
          break;
        case '%':
          op2 = pop();
          if (op2 != 0.0)
            push((int) pop() % (int) op2);
          else
            printf("%% By Zero\n");
          break;
        case '=':
          printf("\t%f\n", push(pop()));
          break;
        case 'c':
          clear();
          break;
        default:
          printf("Unknown Command %c\n", c);
          break;
      }
    } else if (test == 1) {
      push(num);
    }
  }
}
