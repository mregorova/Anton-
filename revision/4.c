#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main () 
{
    char arr[20][20];
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            arr[i][j] = 'N';

    int n = 0;
    int mode, x, y;
    char color = '0';


    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &mode);
        if (mode == 1)
        {
            scanf("%d %d %c", &x, &y, &color);
            arr[x][y] = color;
        }

        if (mode == 2)
        {
            scanf("%d %d", &x, &y);
            printf("%c\n", arr[x][y]);
        }
    }

    return 0;
}
