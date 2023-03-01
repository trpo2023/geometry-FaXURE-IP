#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void print(char* arr)
// {
//     float x, y, rad;
//     char del[] = "( ,)";
//     char* tok = strtok(arr, del);
//     printf("\n%s:\n", tok);
//     x = atof(strtok(NULL, del));
//     y = atof(strtok(NULL, del));
//     rad = atof(strtok(NULL, del));
//     printf("\tcenter = (%.3f %.3f)\n\tradius = %.3f\n", x, y, rad);
// }

int main()
{
    FILE* f1;
    FILE* f;

    f1 = fopen("test.txt", "r");

    if (!f1) {
        printf("Err: cannot open f. Check name of f\n");
    }

    int i, op_bracket = 0, cl_bracket = 0, last_num_elem = 0, f_num_elem = 0,
           sec_num_elem = 0, len = 0, counter = 0, elem = 0, err = 0;

    while (true) {
        elem = fgetc(f1);
        if (elem == EOF) {
            if (feof(f1) != 0) {
                break;
            }
        }
        counter++;
    }
    len = counter;
    fclose(f1);

    char arr[len], brr[6] = "circle";
    f = fopen("test.txt", "r");
    while (fgets(arr, len + 1, f)) {
        printf("%s", arr);

        // check 'circle and finding index of op bracket
        for (i = 0; i < 7; i++) {
            if (arr[i] != brr[i] && i < 6) {
                printf("Err at column %d: expected 'circle'\n", i);
                err = 1;
                break;
                ;
            }
            op_bracket = i;
        }
        for (i = 0; i < len; i++) {
            if (arr[i] == ')') {
                cl_bracket = i;
            } else {
                cl_bracket = len - 1;
            }
        }

        // check 1 number
        for (i = op_bracket + 1; arr[i] != ' '; i++) {
            if (err == 0) {
                if (arr[i] == ',') {
                    err = 1;
                    printf("Err at column %d: expected '<space>' and "
                           "'<double>'\n",
                           i);
                    break;
                }
                if (isdigit(arr[i]) == 0 && arr[i] != '.' && arr[i] != '-') {
                    err = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                f_num_elem = i;
            } else {
                break;
            }
        }

        // check second number
        for (i = f_num_elem + 2; arr[i] != ','; i++) {
            if (err == 0) {
                if (arr[i] == ')') {
                    err = 1;
                    printf("Err at column %d: expected ',' and '<double>'\n",
                           i);
                    break;
                }
                if (isdigit(arr[i]) == 0 && arr[i] != '.') {
                    err = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                sec_num_elem = i;
            } else {
                break;
            }
        }

        // check last number
        for (i = sec_num_elem + 3; i < cl_bracket; i++) {
            if (err == 0) {
                if (isdigit(arr[i]) == 0 && arr[i] != '.') {
                    if (arr[i] == ')' || arr[i] == '(' || arr[i] == ' ') {
                        break;
                    }
                    err = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                last_num_elem = i;
            } else {
                break;
            }
        }
        // printf("index of last number = %d\n", last_num_elem);

        // check ')' symbol
        for (i = last_num_elem + 1; i < len; i++) {
            if (err == 0) {
                if (arr[i] != ')') {
                    err = 1;
                    printf("Err at column %d: expected ')'\n", i);
                    break;
                } else {
                    cl_bracket = i;
                    break;
                }
            } else {
                break;
            }
        }
        // printf("')' = %d\n", cl_bracket);

        // check unexpected tokens
        for (i = cl_bracket + 1; i < len; i++) {
            if (err == 0) {
                if (arr[i] == '\n') {
                    break;
                }

                if (arr[i] != ' ') {
                    err = 1;
                    printf("Err at column %d: unexpected token\n", i);
                    break;
                }
            } else {
                break;
            }
        }

        if (err == 0) {
            printf("No Errors!\n\n");
            //print(arr);
        }
        // print(arr);
        err = 0;
        printf("\n\n\n");
    }
    return 0;
}