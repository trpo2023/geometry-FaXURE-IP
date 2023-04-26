#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../src/libgeometry/check.h"
#include "../thirdparty/ctest.h"

CTEST(check_word, correct_word_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    char b[] = "circle";
    int error = 0;
    int result = check_word(a, b, &error);

    ASSERT_EQUAL(6, result);
    ASSERT_EQUAL(0, error);
}

CTEST(search_close_bracket_index, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int length = strlen(a);
    int result = search_close_bracket_index(a, &length);

    ASSERT_EQUAL(20, result);
}

CTEST(search_close_bracket_index, no_close_bracket_test)
{
    char a[] = "circle(0.0, 0.0, 1.0";
    int length = strlen(a);
    int result = search_close_bracket_index(a, &length);

    ASSERT_EQUAL(19, result);
}

CTEST(check_first_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int open_bracket_index = 6, error = 0;
    int result = check_first_number(a, &open_bracket_index, &error);

    ASSERT_EQUAL(9, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_first_number, error_input_test)
{
    char a[] = "circle(0.0x, 0.0, 1.0)";
    int open_bracket_index = 6, error = 1;
    int result = check_first_number(a, &open_bracket_index, &error);

    ASSERT_EQUAL(1, error);
    ASSERT_NOT_EQUAL(11, result);
}

CTEST(check_second_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int first_num_elem_index = 11, error = 0;
    int result = check_second_number(a, &first_num_elem_index, &error);

    ASSERT_EQUAL(14, result);
    ASSERT_EQUAL(0, error);
}

CTEST(check_second_number, error_input_test)
{
    char a[] = "circle(0.0, 0.x, 1.0)";
    int first_num_elem_index = 11, error = 0;
    int result = check_second_number(a, &first_num_elem_index, &error);

    ASSERT_NOT_EQUAL(16, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_third_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int second_num_elem_index = 16, error = 1, close_bracket_index = 17;
    int result = check_third_number(a, &second_num_elem_index, &close_bracket_index, &error);

    ASSERT_EQUAL(0, result);
}

CTEST(check_third_number, error_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.x)";
    int second_num_elem_index = 16, error = 1, close_bracket_index = 17;
    int result = check_third_number(a, &second_num_elem_index, &close_bracket_index, &error);

    ASSERT_NOT_EQUAL(21, result);
    ASSERT_EQUAL(1, error);
}
CTEST(check_close_bracket_index, no_error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int third_num_elem_index = 7, length = strlen(a), error = 0;
    int result = check_close_bracket_index(a, &third_num_elem_index, &length, &error);

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_close_bracket_index, error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0";
    int third_num_elem_index = 7, length = strlen(a), error = 0;
    int result = check_close_bracket_index(a, &third_num_elem_index, &length, &error);

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_unexpected_tokens, no_error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)\n";
    int close_bracket_index = 14, length = strlen(a), error = 0;
    int result = check_unexpected_tokens(a, &close_bracket_index, &length, &error);

    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_unexpected_tokens, error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)x";
    int close_bracket_index = 14, length = strlen(a), error = 0;
    int result = check_unexpected_tokens(a, &close_bracket_index, &length, &error);

    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error);
}

CTEST(token, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    float x = 0.0, y = 0.0, radius = 0.0;
    token(a, &x, &y, &radius);

    ASSERT_EQUAL(0.0, x);
    ASSERT_EQUAL(0.0, y);
    ASSERT_EQUAL(1.0, radius);
}

CTEST(token, incorrect_input_test)
{
    char a[] = "circle(0, 0, 1)";
    float x = 0.0, y = 0.0, radius = 0.0;
    token(a, &x, &y, &radius);

    ASSERT_EQUAL(0.0, x);
    ASSERT_EQUAL(0.0, y);
    ASSERT_EQUAL(1.0, radius);
}
