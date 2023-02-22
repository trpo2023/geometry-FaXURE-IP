#include <stdio.h>
#include <string>
#include <typeinfo>
#include <cstring>
#include <ctype.h>

void print(char* a) {
  float x, y, rad;
  char del[] = "( ,)";
  char* tok = strtok(a, del);
  printf("\n%s:\n", tok);
  x = atof(strtok(NULL, del));
  y = atof(strtok(NULL, del));
  rad = atof(strtok(NULL, del));
  printf("\tcenter = (%.3f %.3f)\n\tradius = %.3f\n", x, y, rad);
}

int main() {
  FILE* file;
  char a[100], b[] = "circle";
  float j, z, d;
  int i;

  file = fopen("/home/gopotron/geometry-FaXURE-IP/src/test.txt", "r");
  fgets(a, 100, file);
  // check 'circle'
  for (i = 0; i < 7; i++) {
    if (a[i] != b[i] && i < 6) {
      printf("Error at column %d: expected 'circle'\n", i);
      return 0;
    }
    j = i;
  }
  // check numbers
  for (i = j + 1; a[i] != ','; i++) {
    if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != ' ' && a[i] != ',') {
      printf("Error at column %d: expected '<double>'\n", i);
      return 0;
    }
    z = i;
  }
  for (i = z + 2; i < int(strlen(a)) - 1; i++) {
    if (isdigit(a[i]) == 0 && a[i] != ' ' && a[i] != '.') {
      printf("Error at column %d: expected '<double>'\n", i);
      return 0;
    }
    d = i;
  }
  if (a[int(strlen(a))] == ')') {
    printf("Error at column %d: expected ')'\n", i);
    return 0;
  }
  printf("No Errors!");
  print(a);

  return 0;
}