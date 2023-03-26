#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    FILE* f1;
    FILE* f;

    f1 = fopen("test.txt", "r");

    if (!f1) {
        printf("Err: cannot open f. Check name of f\n");
    }

    int i, open_bracket = 0, close_bracket = 0, third_num_elementent = 0,
           first_num_elementent = 0, second_num_elementent = 0, length = 0,
           counter = 0, element = 0, flag = 0;

    while (1) {
        element = fgetc(f1);
        if (element == EOF) {
            if (feof(f1) != 0) {
                break;
            }
        }
        counter++;
    }
    length = counter;
    fclose(f1);

    char array[length], Barray[6] = "circle";
    f = fopen("test.txt", "r");
    while (fgets(array, length + 1, f)) {
        printf("%s", array);

        // check 'circle and finding index of op bracket
        for (i = 0; i < 7; i++) {
            if (array[i] != Barray[i] && i < 6) {
                printf("Err at column %d: expected 'circle'\n", i);
                flag = 1;
                break;
                ;
            }
            open_bracket = i;
        }
        for (i = 0; i < length; i++) {
            if (array[i] == ')') {
                close_bracket = i;
            } else {
                close_bracket = length - 1;
            }
        }

        // check 1 number
        for (i = open_bracket + 1; array[i] != ' '; i++) {
            if (flag == 0) {
                if (array[i] == ',') {
                    flag = 1;
                    printf("Err at column %d: expected '<space>' and "
                           "'<double>'\n",
                           i);
                    break;
                }
                if (isdigit(array[i]) == 0 && array[i] != '.'
                    && array[i] != '-') {
                    flag = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                first_num_elementent = i;
            } else {
                break;
            }
        }

        // check second number
        for (i = first_num_elementent + 2; array[i] != ','; i++) {
            if (flag == 0) {
                if (array[i] == ')') {
                    flag = 1;
                    printf("Err at column %d: expected ',' and '<double>'\n",
                           i);
                    break;
                }
                if (isdigit(array[i]) == 0 && array[i] != '.') {
                    flag = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                second_num_elementent = i;
            } else {
                break;
            }
        }

        // check last number
        for (i = second_num_elementent + 3; i < close_bracket; i++) {
            if (flag == 0) {
                if (isdigit(array[i]) == 0 && array[i] != '.') {
                    if (array[i] == ')' || array[i] == '(' || array[i] == ' ') {
                        break;
                    }
                    flag = 1;
                    printf("Err at column %d: expected '<double>'\n", i);
                    break;
                }
                third_num_elementent = i;
            } else {
                break;
            }
        }

        // check ')' symbol
        for (i = third_num_elementent + 1; i < length; i++) {
            if (flag == 0) {
                if (array[i] != ')') {
                    flag = 1;
                    printf("Err at column %d: expected ')'\n", i);
                    break;
                } else {
                    close_bracket = i;
                    break;
                }
            } else {
                break;
            }
        }

        // check unexpected tokens
        for (i = close_bracket + 1; i < length; i++) {
            if (flag == 0) {
                if (array[i] == '\n') {
                    break;
                }

                if (array[i] != ' ') {
                    flag = 1;
                    printf("Err at column %d: unexpected token\n", i);
                    break;
                }
            } else {
                break;
            }
        }

        if (flag == 0) {
            printf("No Errors!\n\n");
            // print(array);
        }
        // print(array);
        flag = 0;
        printf("\n\n\n");
    }
    return 0;
}