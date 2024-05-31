#include <stdio.h>
#include <math.h>

int htoi(char *hex);

main () {
  char ex[10][5] = {
    "FDAB",
    "1343",
    "adf5",
    "1468",
    "3491",
    "19f8",
    "ab73",
    "67fc",
    "13fa",
    "39DE"
  };
  int i;
  for (i = 0; i < 10; ++i) {
    int res = htoi(ex[i]);
    printf("Hex: %s, Res: %d\n", ex[i], res);
  }
}

int htoi(char *hex) {
  int i;
  int res = 0;
  for (i = 0; hex[i] != '\0'; ++i) {
    int digitValue = 0;
    if (hex[i] >= '0' && hex[i] <= '9')
      digitValue = hex[i] - '0';
    else if (hex[i] >= 'A' && hex[i] <= 'F')
      digitValue = hex[i] - 'A' + 10;
    else if (hex[i] >= 'a' && hex[i] <= 'f')
      digitValue = hex[i] - 'a' + 10;
    else
      break;
    res = (res * 16) + digitValue;
  }
  return res;
}
