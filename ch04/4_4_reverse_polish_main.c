#include <stdio.h>

#define MAXOP 20
#define NUMBER '0'
#define TOOBIG '9'

int main()
{
  int type;
  char s[MAXOP], getop();
  double op2, push(). pop(), atof();

  while ((type = getop(s, MAXOP)) != EOF)
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
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
      case TOOBIG:
        printf("%.20s ... is too long\n", s);
        break;
      default:
        printf("Unknown Command %c\n", type);
        break;
    }
  return 0;
}
