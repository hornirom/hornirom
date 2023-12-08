#include <stdio.h>
#include <string.h>
#include <math.h>

int vstup (char c[]) {
    int i;
    int k = 0;
    for (i = 0; c[i] != '\0'; i++) {
        if (((int)c[i] < 97 || (int)c[i] > 122) && c[i] != '|') return 1;
        else if (c[i] == '|') k++;
    }
    if (k == 1) return 0;
    return 1;
}

void cut (char c[], char x[], char y[]) {
    int i, n = 0;
    int len = strlen(c);
    for (i = 0; i < len; i++) {
        if (c[i] == '|') n = i;
    }
    strncpy(x, c + 0, n);
    strncpy(y, c + n+1, strlen(c)-n-1);
}

void convert (char c[], long long *x) {
    int i;
    int k = 0;
    for (i = 0; c[i] != '\0'; i++) {
        *x = pow(2, (int)c[i] - 97);
        k = k + *x;
    }
    *x = k;
}

int div (long long x, long long y) {
    if (x == 0) return y;
    return div(y%x, x);
}

int check (long long x, long long y, long long z) {
    int k = div(x, y);
    return (z%k == 0);
}

int solution (long long x, long long y, long long z) {
    int i = 0;
    while (i >= 0) {
        if ((z - x*i) % y == 0) return i;
        else i++;
    }
    return i;
}

int main () {

    printf("Zpravy:\n");

    char m1[5000], m2[5000];
    scanf("%s", m1);
    scanf("%s", m2);

    if (m1[0] == '\0' || m2[0] == '\0') printf("Nespravny vstup.\n");
    else if (vstup(m1) || vstup(m2)) printf("Nespravny vstup.\n");
    else {
        char x1[5000], x2[5000], y1[5000], y2[5000];
        cut(m1, x1, y1);
        cut(m2, x2, y2);

        long long a = 0, x = 0, b = 0, y = 0;
        convert(x1, &a);
        convert(y1, &x);
        convert(x2, &b);
        convert(y2, &y);

        if ((a + x == 0) || (b +  y == 0)) printf("Nespravny vstup.\n");
        else if (a == 0 || b == 0 || x == 0 || y == 0) printf("Synchronizace za: 0\n");
        else if (check(x+a, y+b, b-a)) {
            printf("Synchronizace za: %lld\n", a + (x + a) * solution(x+a, y+b, b-a));
        }
        else printf("Nelze dosahnout.\n");
    }

    return 0;
}
