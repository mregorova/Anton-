#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
    int n, sum, ex;
    sum = 0;
    scanf("%d", &n);
    int* arr = (int*) calloc(n, sizeof(int));
    int str;

    for (int i = 0; i < n; i++) {
        scanf("%d", &str);
        sum += str;
        arr[i] = str;
    }

    ex = sum / n;
    for (int i = 0; i < n; i++) {
        int result = ex - arr[i];
        printf("%d\n", result);
    }


    return 0;
}
