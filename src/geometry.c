#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
    float x, y;
};

void init_Input(char array[32])
{
    scanf("%[^\n]", array);
}

void Circle_Info(float x, float y, float rad)
{
    printf("\tcenter = (%.3f %.3f)\n\tradius = %.3f\n", x, y, rad);
}

int main()
{
    char* input = malloc(sizeof(char) * 32);
    init_Input(input);
    char del[] = "( ,)";
    char* token = strtok(input, del);
    if (strcmp(token, "circle") == 0) {
        printf("\n%s:\n", token);
        struct Point p;

        p.x = atof(strtok(NULL, del));
        p.y = atof(strtok(NULL, del));
        float rad = atof(strtok(NULL, del));

        Circle_Info(p.x, p.y, rad);

    } else {
        printf("Invalid value.\n");
    }
    free(input);
    return 0;
}