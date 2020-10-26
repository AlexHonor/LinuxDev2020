#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int* data = (int*)malloc(sizeof(int) * 100);
  
  printf("%d", data);
  
  free(data);
  free(data);
  
  return 0;
}