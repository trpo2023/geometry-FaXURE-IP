#define _USE_MATH_DEFINES
#include "check.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double sqroot(double square)
{
    double root = square / 3;
    int i;
    if (square <= 0)
        return 0;
    for (i = 0; i < 32; i++)
        root = (root + square / root) / 2;
    return root;
}

int check_word(char* a, char* b, int* error)
{
    int open_bracket_index;

    for (int i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            printf("Error at column %d: expected 'circle'\n", i);
            *error = 1;
            break;
        }
        open_bracket_index = i;
    }
    return open_bracket_index;
}

int search_close_bracket_index(char* a, int* length)
{
    int close_bracket_index;

    for (int i = 0; i < *length && a[i] != '\n'; i++) {
        if (a[i] == ')') {
            close_bracket_index = i;
        } else {
            close_bracket_index = *length - 1;
        }
    }
    return close_bracket_index;
}

int check_first_number(char* a, int* open_bracket_index, int* error)
{
    int first_num_elem_index = 0;

    for (int i = *open_bracket_index + 1; a[i] != ' '; i++) {
        if (*error == 0) {
            if (a[i] == ',') {
                *error = 1;
                printf("\nError at column %d: expected '<space>' and "
                       "'<double>'",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-'
                && a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            first_num_elem_index = i;
        } else
            break;
    }
    return first_num_elem_index;
}

int check_second_number(char* a, int* first_num_elem_index, int* error)
{
    int second_num_elem_index = 0;
    for (int i = *first_num_elem_index + 2; a[i] != ','; i++) {
        if (*error == 0) {
            if (a[i] == ')') {
                *error = 1;
                printf("\nError at column %d: expected ',' and '<double>'", i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
                *error = 1;
                printf("\nError at column %d: expected '<double>' or ',' "
                       "token",
                       i);
                break;
            }
            second_num_elem_index = i;
        } else
            break;
    }
    return second_num_elem_index;
}

int check_third_number(
        char* a,
        int* second_num_elem_index,
        int* close_bracket_index,
        int* error)
{
    int third_num_elem_index = 0;

    for (int i = *second_num_elem_index + 3; i < *close_bracket_index; i++) {
        if (*error == 0) {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                    break;
                }
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            third_num_elem_index = i;
        } else
            break;
    }
    return third_num_elem_index;
}

int check_close_bracket_index(
        char* a, int* third_num_elem_index, int* length, int* error)
{
    int close_bracket_index = 0;

    for (int i = *third_num_elem_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] != ')') {
                *error = 1;
                printf("\nError at column %d: expected ')'", i);
                break;
            } else {
                close_bracket_index = i;
                break;
            }
        } else
            break;
    }
    return close_bracket_index;
}

int check_unexpected_tokens(
        char* a, int* close_bracket_index, int* length, int* error)
{
    for (int i = *close_bracket_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] == '\n') {
                break;
            }

            if (a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: unexpected token", i);
                break;
            }
        } else
            break;
    }
    return *error;
}

void token(char* a, float* x, float* y, float* radius) // change
{
    float square, perimeter;
    char del[] = "circle( ,)";
    *x = atof(strtok(a, del));                                      // change
    *y = atof(strtok(NULL, del));                                   // change
    *radius = atof(strtok(NULL, del));                              // change
    square = M_PI * *radius * *radius;                              // change
    perimeter = 2 * M_PI * *radius;                                 // change
    printf("x = %.3f\ty = %.3f\tradius = %.3f\n", *x, *y, *radius); // change
    printf("square = %.3f\tperimeter = %.3f\n", square, perimeter);
}

void intersects(
        float* x_arr, float* y_arr, float* radius_arr, int figure_amount)
{
    int intersections_amount = 0;
    printf("\nIntersections:\n");
    for (int i = 0; i < figure_amount; i++) {
        intersections_amount = 0;
        printf("\ncircle %d. intersects ", i);
        for (int j = 0; j < figure_amount; j++) {
            // distance between centers
            double r = sqrt(x_arr[j] - x_arr[i]) * (x_arr[j] - x_arr[i])
                    + (y_arr[j] - y_arr[i]) * (y_arr[j] - y_arr[i]);
            r = sqroot(r);
            // checking for the coincidence of two circles
            if (r == 0 && radius_arr[i] == radius_arr[j] && j != i) {
                // intersects
                intersections_amount++;
                printf("circle %d.\t", j);
            }
            // checking for the intersection of circles according to the
            // triangle rule
            if (radius_arr[i] + radius_arr[j] >= r
                && radius_arr[i] + r >= radius_arr[j]
                && r + radius_arr[j] >= radius_arr[i] && j != i) {
                // intersects
                intersections_amount++;
                printf("circle %d.\t", j);
            }
        }
    }
    if (intersections_amount == 0) {
        printf("nothing");
    }
    puts("\n");
}