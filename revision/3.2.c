#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int func(int n, int str, int *arr) {


    for (int i = 0; i < n; i++) {
        scanf("%d", &str);
        arr[i] = str;

        if (arr[i] % 2 == 0) {
            arr[i] *= 2;
        } else {
            arr[i] += 2;
        }
    }

    return arr;

}

int main() {

    int n = 0;
    int str = 0;
    scanf("%d", &n);
    int *arr = (int*)calloc(n, sizeof(int));

    func(n, str, arr);

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
