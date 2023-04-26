#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libgeometry/check.h"

int main()
{
    FILE* file1;
    FILE* file;
    file1 = fopen("geometry.txt", "r");
    if (!file1) {
        printf("Error! Cannot open file. Check file name.\n");
        return 0;
    }
    int length = 0, count = 0, element = 0, error = 0;
    while (1) {
        element = fgetc(file1);
        if (element == EOF) {
            if (feof(file1) != 0) {
                break;
            }
        }
        count++;
    }
    length = count;
    fclose(file1);
    int figure_amount = 0;
    float* x_arr = (float*)malloc(figure_amount * sizeof(float));
    float* y_arr = (float*)malloc(figure_amount * sizeof(float));
    float* radius_arr = (float*)malloc(figure_amount * sizeof(float));

    char a[length], b[6] = "circle";
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file)) {
        printf("%s", a);

        int open_bracket_index = check_circle_word(a, b, &error);

        int close_bracket_index = search_close_bracket_index(a, &length);

        int first_num_elem_index
                = check_first_number(a, &open_bracket_index, &error);

        int second_num_elem_index
                = check_second_number(a, &first_num_elem_index, &error);

        int third_num_elem_index = check_third_number(
                a, &second_num_elem_index, &close_bracket_index, &error);

        close_bracket_index = get_close_bracket_index(
                a, &third_num_elem_index, &length, &error);

        error = check_unexpected_tokens(
                a, &close_bracket_index, &length, &error);

        if (error == 0) {
            printf("No Errors!\n");
            float x = 0, y = 0, radius = 0;
            parse_circle_expression(a, &x, &y, &radius);
            x_arr[figure_amount] = x;
            y_arr[figure_amount] = y;
            radius_arr[figure_amount] = radius;
            figure_amount += 1;
        }

        error = 0;
        printf("\n");
    }

    find_intersections(x_arr, y_arr, radius_arr, figure_amount);
    return 0;
}