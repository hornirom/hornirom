#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    int year;
    int month;
    int day;
    int rating;
    char comment[4097];
}Review;

int prestupny (int y) {
    return ( y % 4 == 0 && !(y % 100 == 0 && y % 400 != 0) );
}

int isWrongDay ( Review *x ) {
    return ( ( x->year < 1800 || x->year > 3000 || x->day > 31 || x->month > 12 || x->day < 1 || x->month < 1 ) || ( !prestupny(x->year) && x->month == 2 && x->day > 28 ) || ( prestupny(x->year) && x->month == 2 && x->day > 29 ) || ( x->month > 8 && x->month % 2 == 1 && x->day == 31 ) || ( x->month < 8 && x->month % 2 == 0 && x->day == 31 ) );
}

int isEarlier ( Review *x , Review * reviews, int count ) {
    return ( ( (reviews+count-1)->year > x->year ) || ( (reviews+count-1)->year == x->year && (reviews+count-1)->month > x->month ) || ( (reviews+count-1)->year == x->year && (reviews+count-1)->month == x->month && (reviews+count-1)->day > x->day ) );
}

int compare ( const void* x, const void* y ) {
    return ( *(int*)x - *(int*)y );
}

void answer ( char rule, Review* array, int step, int count) {
    if ( count == 1 ) {
        printf("%d-%02d-%02d - %d-%02d-%02d: %lf %d\n", array->year, array->month, array->day, array->year, array->month, array->day, (double)array->rating, array->rating);
        if ( rule == '?' ) printf("  %d: %s\n", array->rating, array->comment);
    }
    else {
        int startingYear = 0, startingMonth = 0, startingDay = 0, endingYear = 0, endingMonth = 0, endingDay = 0;
        int medianOut = 0;
        double averageOut = 0;
        int startingPoint = 0, endingPoint = 0;
        double diff = 0.0;
        int *ratingArray;
        if ( step == 1 ) step++;

        for ( int i = 0; i <= count - step; i++ ) {
            int identicals = 0;
            for ( int j = i; j < count - step; j++ ) {
                if ( (array+j)->year == (array+j+1)->year && (array+j)->month == (array+j+1)->month && (array+j)->day == (array+j+1)->day ) {
                    identicals++;
                }
                else break;
            }
            for ( int ending = i + step; ending <= count; ending++ ) {
                int end = ending;
                for ( int j = ending; j < count; j++ ) {
                    if ( (array+j)->year == (array+j - 1)->year && (array+j)->month == (array+j - 1)->month && (array+j)->day == (array+j - 1)->day ) {
                        end = j + 1;
                    }
                    else break;
                }

                double average = 0;
                for ( int j = i; j < end; j++ ) {
                    average += (array+j)->rating;
                }
                average = average / ( end - i );

                int size = end - i;
                ratingArray = (int *) calloc(size, sizeof(int));
                for ( int r = 0; r < end - i; r++ ) {
                    ratingArray[r] = (array+i + r)->rating;
                }
                qsort(ratingArray, end-i, sizeof(int), compare);
//            for ( int j = 0; j < end - start; j++ ) {
//                printf("%d ", ratingArray[j]);
//            }
                //printf("%d\n", (end - start - 1) / 2 );
                int median = ratingArray[ ( end - i - 1 ) / 2 ];
                free(ratingArray);
                //printf("N %d | START %d | END %d | MEDIAN %lld\n", currentStep, start, end, median);
                double difference = fabs(average - (double)median);
                //printf("AV %lf | MEDIAN %d | DIFF %lf | START %d | END %d\n", average, median, difference, i, end );
                if ( difference > diff) {
                    diff = difference;
                    startingYear = (array+i)->year;
                    startingMonth = (array+i)->month;
                    startingDay = (array+i)->day;
                    endingYear = (array+end - 1)->year;
                    endingMonth = (array+end - 1)->month;
                    endingDay = (array+end - 1)->day;
                    averageOut = average;
                    medianOut = median;
                    startingPoint = i;
                    endingPoint = end;
                }
                else if ( difference == diff && ( (array+end - 1)->year > endingYear || ((array+end - 1)->year == endingYear && (array+end - 1)->month > endingMonth) || ((array+end - 1)->year == endingYear && (array+end - 1)->month == endingMonth && (array+end - 1)->day > endingDay )) ) {
                    startingYear = (array+i)->year;
                    startingMonth = (array+i)->month;
                    startingDay = (array+i)->day;
                    endingYear = (array+end - 1)->year;
                    endingMonth = (array+end - 1)->month;
                    endingDay = (array+end - 1)->day;
                    averageOut = average;
                    medianOut = median;
                    startingPoint = i;
                    endingPoint = end;
                }
                else if ( difference == diff && (array+end - 1)->year == endingYear && (array+end - 1)->month == endingMonth && (array+end - 1)->day == endingDay && (( startingYear > (array+i)->year ) || ( startingYear == (array+i)->year && startingMonth > (array+i)->month ) || ( startingYear == (array+i)->year && startingMonth == (array+i)->month && startingDay > (array+i)->day)) ) {
                    startingYear = (array+i)->year;
                    startingMonth = (array+i)->month;
                    startingDay = (array+i)->day;
                    averageOut = average;
                    medianOut = median;
                    startingPoint = i;
                    endingPoint = end;
                }
                ending = end;
            }
            i += identicals;
        }

        printf("%d-%02d-%02d - %d-%02d-%02d: %lf %d\n", startingYear, startingMonth, startingDay, endingYear, endingMonth, endingDay, averageOut, medianOut);

        if ( rule == '?' ) {
            for ( int i = startingPoint; i < endingPoint; i++ ) {
                printf("  %d: %s\n", (array+i)->rating, (array+i)->comment);
            }
        }
    }
}

int main() {
    printf("Recenze:\n");
    Review * arrayOfReviews;
    int count = 0;
    int size = 20;
    arrayOfReviews = (Review *) calloc(size, sizeof(Review));
    //printf("%d\n", size);
    while (1) {
        char rule;
        Review input;
        //printf("%d\n", size);
        int ch = scanf(" %c", &rule);
        if ( ch == EOF ) {
            break;
        }
        else if ( ch != 1 ) {
            printf("Nespravny vstup.\n");
            break;
        }
        else {
            if ( rule == '+' ) {
                int scan = scanf("%d-%d-%d %d %4096s", &input.year, &input.month, &input.day, &input.rating, input.comment);
                if ( scan != 5 || ( input.rating < 1 || isWrongDay(&input) ) || ( count > 0 && isEarlier(&input, arrayOfReviews, count) ) ) {
                    printf("Nespravny vstup.\n");
                    break;
                }
                else if ( size == count + 1 ) {
                    //printf("SIZE\n");
                    size *= 2;
                    arrayOfReviews = (Review *) realloc(arrayOfReviews, size * sizeof(Review));
                }
                //printf("%d | %d\n", count, size);
                arrayOfReviews[count] = input;
                count++;
            }
            else if ( rule == '#' || rule == '?' ) {
                int step = 0;
                int scan = scanf(" %d", &step);
                if ( scan != 1 || step < 1 || count < 1 ) {
                    printf("Nespravny vstup.\n");
                    break;
                }
                else if ( step > count ) {
                    printf("Neexistuje.\n");
                }
                else {
                    answer( rule, arrayOfReviews, step, count );
                }
            }
            else {
                printf("Nespravny vstup.\n");
                break;
            }
        }
    }
    free(arrayOfReviews);
    return 0;
}
