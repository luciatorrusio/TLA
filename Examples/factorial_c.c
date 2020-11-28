#include <stdio.h>
int factorial(int x);
int factorial(int x) {
  int resp = 1;
  int i = 1;
  while(i <= x) {
    resp = resp * i;
    i++;
  }

  return resp;
}

int main() {
  int var = factorial(5 % 10);

  
  printf("Resultado:%d", var);

  return 0;
}