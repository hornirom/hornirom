#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef struct
{
    int m_TotalDays;
    int m_WorkDays;
} TResult;
#endif /* __PROGTEST__ */


int prestupny (int y) {
    if (y % 4 == 0 && !(y % 100 == 0 && y % 400 != 0) && y % 4000 != 0) return 1;
    else return 0;
}

int isWrongDate ( int y, int m, int d) {
    if (y < 2000 || m > 12 || m < 1 || d > 31 || d < 1 || (m < 8 && m % 2 == 0 && d == 31) || (m >= 8 && m % 2 == 1 && d == 31)) return 1;
    else return 0;
}

bool isWorkDay ( int y, int m, int d ) {
    if (isWrongDate(y, m, d)) return false;

    if ((!prestupny(y) && m == 2 && d > 28) || (prestupny(y) && m == 2 && d > 29)) return false;

    int svatek = 0;
    if ((m == 1 && d == 1) || (m == 5 && d == 1) || (m == 5 && d == 8) || (d == 5 && m == 7) ||
        (d == 6 && m == 7) || (d == 28 && m == 9) || (d == 28 && m == 10) || (d == 17 && m == 11) ||
        (d == 24 && m == 12) || (d == 25 && m == 12) || (d == 26 && m == 12)) svatek = 1;

    if (m < 3) {
        m = m + 12;
        y = y - 1;
    }
    int w = (d + (int)((m + 1) * 26 / 10) + y + (int)(y / 4) + 6 * (int)(y / 100) + (int)(y / 400) + 6 * (int)(y / 4000)) % 7;
    if (w > 1 && !svatek) return true;
    else return false;
}

void counting ( int y, int m, int d, int *total, int *work) {
    *total += 1;
    if (isWorkDay(y, m, d) == true) *work += 1;
}

void next ( int *y, int *m, int *d) {
    if (*m == 12 && *d == 31) {
        *m = 1;
        *d = 1;
        *y += 1;
    }
    else if ((*m % 2 == 1 && *d == 31 && *m < 8) || (*m % 2 == 1 && *d == 30 && *m >= 8) || (!prestupny(*y) && *m == 2 && *d == 28) || (prestupny(*y) && *m == 2 && *d == 29) || (*m % 2 == 0 && *d == 30 && *m < 8) || (*m % 2 == 0 && *d == 31 && *m >= 8)) {
        *m += 1;
        *d = 1;
    }
    else {
        *d += 1;
    }
}

TResult countDays ( int y1, int m1, int d1, int y2, int m2, int d2 ) {
    TResult count;
    count.m_TotalDays = -1;
    count.m_WorkDays = -1;

    if ((y1 > y2) || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) return count;
    else if (isWrongDate(y1, m1, d1) || isWrongDate(y2, m2, d2)) return count;
    else if ((!prestupny(y1) && m1 == 2 && d1 > 28) || (prestupny(y1) && m1 == 2 && d1 > 29) || (!prestupny(y2) && m2 == 2 && d2 > 28) || (prestupny(y2) && m2 == 2 && d2 > 29)) return count;

    int k = 0, totalDec = 0, workDec = 0;
    int savey = y1, savem = m1, saved = d1;
    count.m_WorkDays = 0, count.m_TotalDays = 0;

    int q = 0, d = -1;
    if (y2 - y1 > 28000) {
        q = (y2 - y1) / 28000;
        d = (y2 - y1) % 28000;
        y2 = y1 + 28000 + d;

        while (k == 0) {
            //printf("d: %d  m: %d  y: %d | count: %d\n", d1, m1, y1, totalCount);
            counting(y1, m1, d1, &totalDec, &workDec);
            counting(y1 + 4000, m1, d1, &totalDec, &workDec);
            counting(y1 + 8000, m1, d1, &totalDec, &workDec);
            counting(y1 + 12000, m1, d1, &totalDec, &workDec);
            counting(y1 + 16000, m1, d1, &totalDec, &workDec);
            counting(y1 + 20000, m1, d1, &totalDec, &workDec);
            counting(y1 + 24000, m1, d1, &totalDec, &workDec);
            next(&y1, &m1, &d1);
            if (y1 >= savey + 4000 && m1 >= savem && d1 >= saved) k += 1;
        }
        //printf("total %d | work %d\n", totalDec, workDec);
        //printf("YEAR1 %d  YEAR %d\n", y1, y2);
        //printf("DEC %d %d %d\n", y1, m1, d1);
        while (k == 1) {
            if (y1 + 24000 >= y2 && m1 >= m2 && d1 >= d2) k += 1;
            counting(y1 + 24000, m1, d1,&count.m_TotalDays, &count.m_WorkDays);
            next(&y1, &m1, &d1);
        }
    }
    else if (y2 - y1 > 20000) {
        q = (y2 - y1) / 20000;
        d = (y2 - y1) % 20000;
        y2 = y1 + 20000 + d;

        while (k == 0) {
            //printf("d: %d  m: %d  y: %d | count: %d\n", d1, m1, y1, totalCount);
            counting(y1, m1, d1, &totalDec, &workDec);
            counting(y1 + 4000, m1, d1, &totalDec, &workDec);
            counting(y1 + 8000, m1, d1, &totalDec, &workDec);
            counting(y1 + 12000, m1, d1, &totalDec, &workDec);
            counting(y1 + 16000, m1, d1, &totalDec, &workDec);
            next(&y1, &m1, &d1);
            if (y1 >= savey + 4000 && m1 >= savem && d1 >= saved) k += 1;
        }
        //printf("total %d | work %d\n", totalDec, workDec);
        //printf("YEAR1 %d  YEAR %d\n", y1, y2);
        //printf("DEC %d %d %d\n", y1, m1, d1);
        while (k == 1) {
            if (y1 + 20000 >= y2 && m1 >= m2 && d1 >= d2) k += 1;
            counting(y1 + 20000, m1, d1,&count.m_TotalDays, &count.m_WorkDays);
            next(&y1, &m1, &d1);
        }
    }
    else if (y2 - y1 > 12000) {
        q = (y2 - y1) / 12000;
        d = (y2 - y1) % 12000;
        y2 = y1 + 12000 + d;

        while (k == 0) {
            //printf("d: %d  m: %d  y: %d | count: %d\n", d1, m1, y1, totalCount);
            counting(y1, m1, d1, &totalDec, &workDec);
            counting(y1 + 4000, m1, d1, &totalDec, &workDec);
            counting(y1 + 8000, m1, d1, &totalDec, &workDec);
            next(&y1, &m1, &d1);
            if (y1 >= savey + 4000 && m1 >= savem && d1 >= saved) k += 1;
        }
        //printf("total %d | work %d\n", totalDec, workDec);
        //printf("YEAR1 %d  YEAR %d\n", y1, y2);
        //printf("DEC %d %d %d\n", y1, m1, d1);
        while (k == 1) {
            if (y1 + 12000 >= y2 && m1 >= m2 && d1 >= d2) k += 1;
            counting(y1 + 12000, m1, d1,&count.m_TotalDays, &count.m_WorkDays);
            next(&y1, &m1, &d1);
        }
    }
    else {
        while (k == 0) {
            if (y1 >= y2 && m1 >= m2 && d1 >= d2) k += 1;
            counting(y1, m1, d1,&count.m_TotalDays, &count.m_WorkDays);
            next(&y1, &m1, &d1);
            //printf("Kd: %d  m: %d  y: %d | count: %d\n", d1, m1, y1, count.m_TotalDays);

        }
    }
    //if(isWorkDay(y1, m1 ,d1) == true) workCount++;
    count.m_WorkDays += q * workDec;
    count.m_TotalDays += q * totalDec;
    //printf("%d, %d\n", count.m_TotalDays, count.m_WorkDays);
    return count;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TResult r;

    assert ( isWorkDay ( 2023, 10, 10 ) );

    assert ( ! isWorkDay ( 2023, 11, 11 ) );

    assert ( ! isWorkDay ( 2023, 11, 17 ) );

    assert ( ! isWorkDay ( 2023, 11, 31 ) );

    assert ( ! isWorkDay ( 2023,  2, 29 ) );

    assert ( ! isWorkDay ( 2004,  2, 29 ) );

    assert ( isWorkDay ( 2008,  2, 29 ) );

    assert ( ! isWorkDay ( 2001,  2, 29 ) );

    assert ( ! isWorkDay ( 1996,  1,  2 ) );

    r = countDays ( 2023, 11,  1,
                    2023, 11, 30 );
    assert ( r . m_TotalDays == 30 );
    assert ( r . m_WorkDays == 21 );

    r = countDays ( 2023, 11,  1,
                    2023, 11, 17 );
    assert ( r . m_TotalDays == 17 );
    assert ( r . m_WorkDays == 12 );

    r = countDays ( 2023, 11,  1,
                    2023, 11,  1 );
    assert ( r . m_TotalDays == 1 );
    assert ( r . m_WorkDays == 1 );

    r = countDays ( 2023, 11, 17,
                    2023, 11, 17 );
    assert ( r . m_TotalDays == 1 );
    assert ( r . m_WorkDays == 0 );

    r = countDays ( 2023,  1,  1,
                    2023, 12, 31 );
    assert ( r . m_TotalDays == 365 );
    assert ( r . m_WorkDays == 252 );

    r = countDays ( 2024,  1,  1,
                    2024, 12, 31 );
    assert ( r . m_TotalDays == 366 );
    assert ( r . m_WorkDays == 254 );

    r = countDays ( 2000,  1,  1,
                    2023, 12, 31 );
    assert ( r . m_TotalDays == 8766 );
    assert ( r . m_WorkDays == 6072 );

    r = countDays ( 2001,  2,  3,
                    2023,  7, 18 );
    assert ( r . m_TotalDays == 8201 );
    assert ( r . m_WorkDays == 5682 );

    r = countDays ( 2021,  3, 31,
                    2023, 11, 12 );
    assert ( r . m_TotalDays == 957 );
    assert ( r . m_WorkDays == 666 );

    r = countDays ( 2001,  1,  1,
                    2000,  1,  1 );
    assert ( r . m_TotalDays == -1 );
    assert ( r . m_WorkDays == -1 );

    r = countDays ( 2001,  1,  1,
                    2023,  2, 29 );
    assert ( r . m_TotalDays == -1 );
    assert ( r . m_WorkDays == -1 );

    r = countDays ( 2044,  2,  1,
                    2044,  1, 1 );
    assert ( r . m_TotalDays == -1 );
    assert ( r . m_WorkDays == -1 );

    r = countDays ( 2460, 4, 3,
                    5075764, 2, 8 );
    assert ( r . m_TotalDays == 1852984914 );
    assert ( r . m_WorkDays == 1283698975 );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

//int main() {
//    if(isWorkDay(2004, 2, 29) == true) printf("y\n");
//    else printf("n\n");
//    countDays( 2023,  1,  1, 2023, 12, 31);
//    return 0;
//}
