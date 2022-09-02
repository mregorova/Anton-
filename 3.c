#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);
    int *arr = (int*)calloc(n, sizeof(int));
    int str;

    for (int i = 0; i < n; i++) {
        scanf("%d", &str);
        arr[i] = str;

        if (arr[i] % 2 == 0) {
            arr[i] *= 2;
        } else {
            arr[i] += 2;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }


    return 0;
}