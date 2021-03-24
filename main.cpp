#include  <stdio.h>
#include  "vector.c"

//Compiler version gcc  6.3.0

int main()
{
  decVector(a);
  assignStr(&a, "Hello, Hello World!\n");
  outputStr(a);
  add(&a, "Bye!\n", 1);
  outputStr(a);
  printf("%d", strlen("asdfghjk"));
  return 0;
}
