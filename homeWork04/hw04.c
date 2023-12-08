#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
constexpr int MAP_MAX = 200;
#endif /* __PROGTEST__ */

void lineCheck ( int *start, int *end, int radek, int sloupec, int size, int pos[][MAP_MAX], int value ) {
    int s = 0;
    while (s < sloupec) {
        if (value <= pos[radek][s] && *start <= s) *start = s + 1;
        s++;
    }
    s = sloupec + 1;
    while (s < size) {
        if (value <= pos[radek][s]) {
            *end = s;
            break;
        }
        s++;
    }
    //printf("linestart %d | lineend %d | radek %d | sloupec %d | size %d | value %d\n", *start, *end, radek, sloupec, size, value);
}

void colCheck ( int *start, int *end, int radek, int sloupec, int size, int pos[][MAP_MAX], int value ) {
    int s = 0;
    while (s < radek) {
        if (value <= pos[s][sloupec] && *start <= s) *start = s + 1;
        s++;
    }
    s = radek + 1;
    while (s < size) {
        if (value <= pos[s][sloupec]) {
            *end = s;
            break;
        }
        s++;
    }
    //printf("colstart %d | colend %d | radek %d | sloupec %d | size %d | value %d\n", *start, *end, radek, sloupec, sized, value);
}

void castleArea ( int altitude[][MAP_MAX], int size, int area[][MAP_MAX] ) {

    for ( int i = 0; i < size; i++ ) {
        for ( int j = 0; j < size; j++ ) {
            int lineStart = 0, lineEnd = size, columnStart = 0, columnEnd = size;
            int lineArr[MAP_MAX][2], columnArr[MAP_MAX][2];

            //printf("current pos: (%d , %d)\n", i, j);
            lineCheck( &lineStart, &lineEnd, i, j, size, altitude, altitude[i][j] );
            colCheck( &columnStart, &columnEnd, i, j, size, altitude, altitude[i][j] );

            //printf("lStr %d | lEnd %d   |   cStr %d | cEnd %d\n", lineStart, lineEnd, columnStart, columnEnd);

            int control = 0;
            for ( int l = columnStart; l < columnEnd; l++ ) {
                for ( int c = lineStart; c < lineEnd; c++ ) {
                    if ( altitude[i][j] <= altitude[l][c] && i != l && j != c ) {
                        control = 1;
                        break;
                    }
                }
                if ( control == 1 ) break;
            }
            if ( control == 0 ) {
                area[i][j] = ( lineEnd - lineStart ) * ( columnEnd - columnStart );
                printf(" %d", area[i][j]);
            }
            else {
                //printf("LINEARR\n");
                for ( int k = 0; k < columnEnd - columnStart; k++ ) {
                    lineArr[k][0] = 0;
                    //printf("%d", lineArr[k][0]);
                    lineArr[k][1] = lineEnd - lineStart;
                    //printf(" %d\n", lineArr[k][1]);
                }
                //printf("COLUMNARR\n");
                for ( int k = 0; k < lineEnd - lineStart; k++ ) {
                    columnArr[k][0] = 0;
                    //printf("%d", columnArr[k][0]);
                    columnArr[k][1] = columnEnd - columnStart;
                    //printf(" %d\n", columnArr[k][1]);
                }

                //printf("\nUPGLINE\n");
                for ( int line = columnStart; line < columnEnd; line++ ) {
                    for ( int column = lineStart; column < lineEnd; column++ ) {
                        if ( altitude[i][j] <= altitude[line][column] ) {
                            //printf("\nkkk\n");
                            if ( column < j ) lineArr[line - columnStart][0] = column + 1 - lineStart;
                            else if ( column > j ) {
                                lineArr[line - columnStart][1] = column - lineStart;
                                break;
                            }
                        }
                    }
                    //printf("%d %d\n", lineArr[line - columnStart][0], lineArr[line - columnStart][1]);
                }

                //printf("\nUPGCOLUMN\n");
                for ( int column = lineStart; column < lineEnd; column++ ) {
                    for ( int line = columnStart; line < columnEnd; line++ ) {
                        //printf("I %d | LINE %d\n", i, line);
                        if ( altitude[i][j] <= altitude[line][column] ) {
                            //printf("\nkkk\n");
                            if ( line < i ) columnArr[column - lineStart][0] = line + 1 - columnStart;
                            else if ( line > i ) {
                                columnArr[column - lineStart][1] = line - columnStart;
                                break;
                            }
                        }
                    }
                    //printf("%d %d\n", columnArr[column - lineStart][0], columnArr[column - lineStart][1]);
                }

                int P = 1;

//                for ( int line = 0; line < columnEnd - columnStart; line++ ) {
//
//                    int check = 0;
//                    //if ( lineArr[line][0] > j || lineArr[line][1] < j ) break;
//                    //printf("\n%d == %d - %d and %d < %d - %d and %d > %d\n", line, i, columnStart, lineArr[line][0], j, lineStart, lineArr[line][1], j);
//                    if ( line == i - columnStart && lineArr[line][0] <= j - lineStart && lineArr[line][1] >= j - lineStart ) check = 1;
//                    int tetris = lineArr[line][1] - lineArr[line][0];
//                    int plane = tetris;
//                    //printf("PLANE %d\n", plane);
//
//                    for ( int ll = line + 1; ll < columnEnd - columnStart; ll++ ) {
//                        if ( ll == i - columnStart && lineArr[ll][0] <= j - lineStart && lineArr[ll][1] >= j - lineStart ) check = 1;
//                        if ( lineArr[line][0] < lineArr[ll][0] || lineArr[line][1] > lineArr[ll][1] ) break;
//                        else plane += tetris;
//                        //printf("CHECK %d\n", check);
//
//                    }
//
//                    for ( int ll = line - 1; ll >= 0; ll-- ) {
//                        if ( ll == i - columnStart && lineArr[ll][0] <= j - lineStart && lineArr[ll][1] >= j - lineStart ) check = 1;
//                        if ( lineArr[line][0] < lineArr[ll][0] || lineArr[line][1] > lineArr[ll][1] ) break;
//                        else plane += tetris;
//                        //printf("CHECK %d\n", check);
//
//                    }
//
//                    //printf("\nPLANE %d | CHECK %d\n", plane, check);
//                    if ( P < plane && check == 1 ) P = plane;
//                }
//
//                for ( int column = 0; column < lineEnd - lineStart; column++ ) {
//
//                    int check = 0;
//                    //if ( columnArr[column][0] > i || columnArr[column][1] < i ) break;
//                    if (column == j - lineStart && columnArr[column][0] <= i - columnStart && columnArr[column][1] >= i - columnStart ) check = 1;
//                    int tetris = columnArr[column][1] - columnArr[column][0];
//                    int plane = tetris;
//                    //printf("PLANE %d\n", plane);
//
//                    for ( int cc = column + 1; cc < lineEnd - lineStart; cc++ ) {
//                        if ( cc == j - lineStart && columnArr[cc][0] <= i - columnStart && columnArr[cc][1] >= i - columnStart ) check = 1;
//                        if ( columnArr[column][0] < columnArr[cc][0] || columnArr[column][1] > columnArr[cc][1] ) break;
//                        else plane += tetris;
//                        //printf("CHECK %d\n", check);
//
//                    }
//
//                    for ( int cc = column - 1; cc >= 0; cc-- ) {
//                        if ( cc == j - lineStart && columnArr[cc][0] <= i - columnStart && columnArr[cc][1] >= i - columnStart ) check = 1;
//                        if ( columnArr[column][0] < columnArr[cc][0] || columnArr[column][1] > columnArr[cc][1] ) break;
//                        else plane += tetris;
//                        //printf("CHECK %d\n", check);
//
//                    }
//
//                    if ( P < plane && check == 1 ) P = plane;
//                }
                if ( lineEnd - lineStart > P ) P = lineEnd - lineStart;
                if ( columnEnd - columnStart > P ) P = columnEnd - columnStart;

//                int savedLineArr[MAP_MAX][2], savedColumnArr[MAP_MAX][2];
//                for ( int k = 0; k < columnEnd - columnStart; k++ ) {
//                    savedLineArr[k][0] = lineArr[k][0];
//                    savedLineArr[k][1] = lineArr[k][1];
//                }
//                for ( int k = 0; k < lineEnd - lineStart; k++ ) {
//                    savedColumnArr[k][0] = columnArr[k][0];
//                    savedColumnArr[k][1] = columnArr[k][1];
//                }

                for ( int leftWall = 0; leftWall <= j - lineStart; leftWall++ ) {
                    for ( int k = 0; k < columnEnd - columnStart; k++ ) {
                        if (lineArr[k][0] < leftWall ) lineArr[k][0] = leftWall;
                    }

                    for ( int line = 0; line < columnEnd - columnStart; line++ ) {

                        int check = 0;
                        //if ( lineArr[line][0] > j || lineArr[line][1] < j ) break;
                        //printf("\n%d == %d - %d and %d < %d - %d and %d > %d\n", line, i, columnStart, lineArr[line][0], j, lineStart, lineArr[line][1], j);
                        if ( line == i - columnStart && lineArr[line][0] <= j - lineStart && lineArr[line][1] >= j - lineStart ) check = 1;
                        int tetris = lineArr[line][1] - lineArr[line][0];
                        int plane = tetris;
                        //printf("PLANE %d\n", plane);

                        for ( int ll = line + 1; ll < columnEnd - columnStart; ll++ ) {
                            if ( ll == i - columnStart && lineArr[ll][0] <= j - lineStart && lineArr[ll][1] >= j - lineStart ) check = 1;
                            if ( lineArr[line][0] < lineArr[ll][0] || lineArr[line][1] > lineArr[ll][1] ) break;
                            else plane += tetris;
                            //printf("CHECK %d\n", check);

                        }

                        for ( int ll = line - 1; ll >= 0; ll-- ) {
                            if ( ll == i - columnStart && lineArr[ll][0] <= j - lineStart && lineArr[ll][1] >= j - lineStart ) check = 1;
                            if ( lineArr[line][0] < lineArr[ll][0] || lineArr[line][1] > lineArr[ll][1] ) break;
                            else plane += tetris;
                            //printf("CHECK %d\n", check);

                        }

                        //printf("\nPLANE %d | CHECK %d\n", plane, check);
                        if ( P < plane && check == 1 ) P = plane;
                    }
                }


                for ( int ceil = 0; ceil <= i - columnStart; ceil++ ) {
                    for ( int k = 0; k < lineEnd - lineStart; k++ ) {
                        if ( columnArr[k][0] < ceil ) columnArr[k][0] = ceil;
                    }

                    for ( int column = 0; column < lineEnd - lineStart; column++ ) {

                        int check = 0;
                        //if ( columnArr[column][0] > i || columnArr[column][1] < i ) break;
                        if (column == j - lineStart && columnArr[column][0] <= i - columnStart && columnArr[column][1] >= i - columnStart ) check = 1;
                        int tetris = columnArr[column][1] - columnArr[column][0];
                        int plane = tetris;
                        //printf("PLANE %d\n", plane);

                        for ( int cc = column + 1; cc < lineEnd - lineStart; cc++ ) {
                            if ( cc == j - lineStart && columnArr[cc][0] <= i - columnStart && columnArr[cc][1] >= i - columnStart ) check = 1;
                            if ( columnArr[column][0] < columnArr[cc][0] || columnArr[column][1] > columnArr[cc][1] ) break;
                            else plane += tetris;
                            //printf("CHECK %d\n", check);

                        }

                        for ( int cc = column - 1; cc >= 0; cc-- ) {
                            if ( cc == j - lineStart && columnArr[cc][0] <= i - columnStart && columnArr[cc][1] >= i - columnStart ) check = 1;
                            if ( columnArr[column][0] < columnArr[cc][0] || columnArr[column][1] > columnArr[cc][1] ) break;
                            else plane += tetris;
                            //printf("CHECK %d\n", check);

                        }

                        if ( P < plane && check == 1 ) P = plane;
                    }
                }

                printf("% d", P);
                //printf("%d %d | %d %d\n", lineStart, lineEnd, columnStart, columnEnd);
                area[i][j] = P;
                //printf("\n");
                //area[i][j] = ( lineEnd - lineStart) * (columnEnd - columnStart);
            }
        }
        printf("\n");
    }
    printf("\n");
}


#ifndef __PROGTEST__
bool identicalMap ( const int a[][MAP_MAX], const int b[][MAP_MAX], int n ) {
    int k = 0;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            if ( a[i][j] != b[i][j] ) {
                printf("i: %d  j: %d\n", i, j);
                k = 1;

            }
        }
    }
    if ( k == 1 ) return false;
    return true;
}

int main ( int argc, char * argv [] ) {
    static int result[MAP_MAX][MAP_MAX];

    static int alt0[MAP_MAX][MAP_MAX] =
            {
                    { 1, 2 },
                    { 3, 4 }
            };
    static int area0[MAP_MAX][MAP_MAX] =
            {
                    { 1, 2 },
                    { 2, 4 }
            };
    castleArea ( alt0, 2, result );
    assert ( identicalMap ( result, area0, 2 ) );

    static int alt1[MAP_MAX][MAP_MAX] =
            {
                    { 2, 7, 1, 9 },
                    { 3, 5, 0, 2 },
                    { 1, 6, 3, 5 },
                    { 1, 2, 2, 8 }
            };
    static int area1[MAP_MAX][MAP_MAX] =
            {
                    { 1, 12, 2, 16 },
                    { 4, 4, 1, 2 },
                    { 1, 9, 4, 4 },
                    { 1, 2, 1, 12 }
            };
    castleArea ( alt1, 4, result );
    assert ( identicalMap ( result, area1, 4 ) );
    static int alt2[MAP_MAX][MAP_MAX] =
            {
                    { 1, 2, 3, 4 },
                    { 2, 3, 4, 5 },
                    { 3, 4, 5, 6 },
                    { 4, 5, 6, 7 }
            };
    static int area2[MAP_MAX][MAP_MAX] =
            {
                    { 1, 2, 3, 4 },
                    { 2, 4, 6, 8 },
                    { 3, 6, 9, 12 },
                    { 4, 8, 12, 16 }
            };
    castleArea ( alt2, 4, result );
    assert ( identicalMap ( result, area2, 4 ) );
    static int alt3[MAP_MAX][MAP_MAX] =
            {
                    { 7, 6, 5, 4 },
                    { 6, 5, 4, 5 },
                    { 5, 4, 5, 6 },
                    { 4, 5, 6, 7 }
            };
    static int area3[MAP_MAX][MAP_MAX] =
            {
                    { 12, 6, 2, 1 },
                    { 6, 2, 1, 2 },
                    { 2, 1, 2, 6 },
                    { 1, 2, 6, 12 }
            };
    castleArea ( alt3, 4, result );
    assert ( identicalMap ( result, area3, 4 ) );
    static int alt4[MAP_MAX][MAP_MAX] =
            {
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 2, 1, 1 },
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1 }
            };
    static int area4[MAP_MAX][MAP_MAX] =
            {
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 25, 1, 1 },
                    { 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1 }
            };
    castleArea ( alt4, 5, result );
    assert ( identicalMap ( result, area4, 5 ) );

    static int alt[MAP_MAX][MAP_MAX] = {
            { 237, 58, 494, 522, 689, 451, 205, 361, 721, 584, 460, 584, 513, 49, 165, 712, 633, 116, 268, 354, 762, 424, 949, 998, 263, 929, 943, 857, 676 },
            { 297, 692, 913, 707, 186, 787, 397, 638, 992, 758, 711, 576, 570, 647, 441, 619, 813, 506, 252, 929, 774, 959, 692, 198, 908, 42, 813, 189, 337 },
            { 22, 865, 635, 714, 779, 694, 901, 918, 91, 891, 911, 202, 954, 487, 772, 602, 281, 392, 415, 787, 996, 344, 561, 955, 388, 111, 215, 783, 276 },
            { 756, 120, 298, 622, 107, 364, 753, 802, 265, 671, 245, 508, 582, 447, 463, 422, 220, 65, 703, 612, 480, 842, 608, 176, 403, 916, 565, 866, 483 },
            { 700, 142, 240, 820, 792, 862, 280, 156, 967, 434, 422, 638, 679, 282, 573, 127, 745, 347, 347, 810, 402, 311, 642, 244, 271, 819, 999, 539, 736 },
            { 865, 23, 436, 359, 615, 608, 151, 477, 888, 307, 796, 674, 81, 786, 354, 364, 359, 833, 109, 58, 532, 272, 812, 195, 914, 56, 466, 85, 407 },
            { 358, 821, 272, 733, 609, 631, 348, 218, 782, 177, 458, 442, 973, 133, 875, 759, 839, 239, 471, 672, 701, 529, 556, 325, 342, 751, 591, 750, 569 },
            { 677, 158, 927, 850, 782, 12, 460, 766, 360, 30, 548, 537, 488, 342, 510, 973, 218, 622, 812, 809, 93, 836, 510, 974, 744, 187, 668, 495, 779 },
            { 771, 417, 456, 929, 696, 658, 63, 709, 118, 829, 69, 500, 730, 959, 341, 72, 469, 314, 642, 443, 479, 452, 888, 667, 314, 863, 412, 502, 883 },
            { 907, 281, 654, 324, 89, 935, 21, 747, 999, 82, 218, 180, 151, 718, 910, 110, 59, 335, 932, 726, 977, 375, 205, 781, 264, 872, 96, 479, 636 },
            { 598, 714, 896, 231, 369, 220, 320, 656, 593, 67, 7, 675, 285, 188, 179, 356, 450, 641, 767, 785, 573, 493, 115, 301, 50, 896, 917, 275, 344 },
            { 396, 911, 942, 462, 807, 525, 183, 380, 845, 840, 325, 913, 199, 353, 550, 739, 532, 258, 190, 525, 26, 327, 99, 871, 794, 400, 922, 691, 317 },
            { 549, 387, 65, 460, 330, 527, 620, 855, 711, 352, 53, 903, 677, 318, 454, 382, 220, 194, 266, 479, 736, 792, 857, 415, 891, 728, 210, 643, 2 },
            { 253, 312, 551, 640, 729, 364, 322, 608, 336, 530, 671, 688, 583, 574, 717, 901, 29, 100, 121, 575, 366, 600, 311, 158, 809, 726, 401, 538, 936 },
            { 396, 540, 541, 60, 444, 182, 789, 808, 856, 398, 144, 386, 69, 184, 969, 996, 901, 222, 377, 1, 344, 952, 720, 296, 263, 878, 106, 989, 632 },
            { 996, 278, 380, 888, 171, 441, 332, 705, 230, 492, 562, 980, 988, 948, 402, 172, 270, 398, 74, 492, 775, 427, 836, 727, 147, 485, 342, 378, 943 },
            { 683, 362, 939, 313, 742, 827, 485, 183, 160, 190, 766, 4, 752, 98, 993, 53, 500, 165, 323, 250, 591, 815, 377, 371, 4, 456, 518, 489, 798 },
            { 248, 432, 482, 610, 723, 795, 705, 550, 632, 888, 62, 823, 6, 67, 575, 105, 412, 628, 957, 929, 303, 208, 873, 119, 585, 244, 123, 42, 114 },
            { 964, 192, 363, 748, 674, 325, 471, 822, 30, 373, 454, 271, 788, 277, 277, 855, 205, 734, 619, 185, 692, 548, 841, 252, 421, 960, 837, 665, 435 },
            { 231, 132, 399, 424, 495, 499, 450, 172, 970, 272, 203, 695, 79, 826, 483, 708, 455, 690, 265, 190, 309, 803, 234, 858, 644, 486, 631, 604, 323 },
            { 649, 391, 907, 781, 790, 683, 628, 641, 133, 800, 963, 758, 355, 658, 837, 181, 142, 897, 989, 832, 163, 179, 494, 966, 413, 352, 962, 899, 335 },
            { 566, 574, 984, 309, 833, 765, 451, 516, 393, 92, 650, 546, 55, 760, 901, 713, 949, 435, 207, 846, 424, 392, 9, 955, 886, 327, 720, 590, 289 },
            { 971, 925, 207, 545, 910, 516, 731, 27, 967, 247, 773, 411, 249, 319, 466, 9, 572, 180, 958, 359, 739, 805, 783, 131, 166, 90, 369, 846, 810 },
            { 959, 487, 781, 237, 47, 679, 499, 915, 410, 526, 235, 657, 651, 646, 259, 970, 113, 268, 895, 645, 579, 254, 384, 384, 390, 868, 902, 480, 237 },
            { 748, 291, 197, 588, 72, 786, 635, 103, 285, 550, 513, 163, 785, 523, 815, 432, 782, 137, 897, 402, 384, 542, 981, 639, 278, 717, 29, 146, 620 },
            { 861, 384, 720, 504, 933, 660, 577, 71, 295, 32, 356, 198, 546, 871, 983, 69, 686, 767, 203, 176, 664, 605, 560, 558, 939, 551, 837, 656, 580 },
            { 983, 628, 794, 719, 701, 298, 4, 361, 227, 75, 657, 260, 431, 855, 806, 655, 190, 227, 341, 958, 782, 869, 974, 739, 430, 533, 678, 981, 370 },
            { 687, 914, 705, 667, 60, 777, 368, 358, 781, 730, 938, 857, 739, 198, 640, 946, 356, 295, 488, 935, 989, 798, 69, 210, 773, 808, 640, 306, 839 },
            { 974, 28, 878, 240, 85, 545, 300, 862, 914, 10, 996, 996, 948, 853, 87, 498, 845, 385, 854, 493, 873, 141, 834, 672, 210, 44, 445, 371, 37 }
    };
    static int area[MAP_MAX][MAP_MAX] = {
            { 2, 1, 3, 4, 8, 3, 1, 2, 20, 2, 1, 5, 3, 1, 2, 12, 4, 1, 2, 3, 22, 1, 24, 493, 1, 36, 20, 6, 4 },
            { 3, 4, 49, 4, 1, 12, 2, 4, 180, 14, 10, 3, 2, 8, 2, 5, 30, 6, 1, 49, 2, 48, 4, 1, 10, 1, 8, 1, 2 },
            { 1, 25, 5, 4, 8, 2, 35, 58, 1, 29, 40, 1, 66, 3, 18, 6, 2, 4, 3, 14, 280, 1, 2, 25, 3, 2, 2, 5, 1 },
            { 7, 1, 4, 5, 1, 2, 11, 21, 2, 10, 1, 2, 8, 2, 5, 3, 2, 1, 13, 2, 2, 45, 3, 1, 4, 52, 2, 16, 3 },
            { 3, 3, 2, 15, 11, 28, 2, 1, 84, 4, 2, 5, 14, 1, 6, 1, 20, 2, 2, 24, 2, 2, 6, 3, 2, 17, 580, 2, 7 },
            { 32, 1, 6, 1, 7, 3, 1, 6, 32, 3, 24, 10, 1, 18, 1, 3, 1, 36, 2, 1, 4, 1, 18, 1, 48, 1, 4, 1, 2 },
            { 1, 16, 1, 12, 1, 8, 3, 1, 14, 2, 3, 1, 105, 1, 44, 7, 30, 1, 3, 4, 8, 3, 4, 4, 2, 12, 2, 10, 2 },
            { 2, 1, 64, 18, 16, 1, 8, 16, 2, 1, 8, 4, 2, 2, 3, 98, 1, 6, 18, 12, 1, 25, 1, 156, 5, 1, 6, 1, 12 },
            { 4, 3, 2, 72, 3, 8, 2, 5, 1, 24, 1, 4, 12, 66, 2, 1, 6, 1, 8, 1, 3, 2, 42, 2, 3, 12, 2, 4, 26 },
            { 22, 1, 4, 2, 1, 145, 1, 8, 754, 2, 4, 2, 1, 12, 30, 2, 1, 3, 68, 2, 187, 2, 3, 8, 2, 16, 1, 2, 4 },
            { 5, 4, 25, 1, 4, 1, 4, 8, 3, 2, 1, 15, 3, 2, 1, 4, 5, 14, 21, 28, 6, 6, 2, 3, 1, 42, 30, 1, 3 },
            { 1, 30, 147, 4, 21, 4, 1, 2, 16, 28, 5, 92, 1, 4, 6, 18, 9, 4, 1, 6, 1, 3, 1, 36, 6, 1, 100, 8, 2 },
            { 6, 2, 1, 4, 1, 6, 10, 48, 6, 2, 1, 56, 10, 1, 6, 4, 4, 2, 6, 7, 16, 30, 33, 3, 39, 6, 1, 4, 1 },
            { 1, 2, 9, 12, 18, 2, 1, 5, 1, 5, 10, 10, 4, 5, 12, 56, 1, 2, 3, 18, 2, 8, 2, 1, 12, 3, 4, 2, 104 },
            { 2, 9, 6, 1, 4, 1, 26, 16, 49, 5, 1, 4, 1, 2, 75, 504, 42, 3, 8, 1, 2, 77, 4, 2, 3, 25, 1, 220, 1 },
            { 377, 1, 2, 60, 1, 3, 1, 8, 2, 4, 4, 162, 234, 20, 5, 3, 2, 12, 1, 9, 24, 1, 26, 15, 2, 4, 2, 2, 30 },
            { 4, 2, 70, 1, 8, 38, 4, 2, 1, 3, 14, 1, 4, 2, 364, 1, 10, 1, 3, 1, 6, 22, 3, 3, 1, 4, 9, 3, 12 },
            { 1, 6, 6, 4, 5, 24, 7, 2, 4, 63, 1, 22, 1, 2, 5, 2, 2, 9, 90, 36, 2, 1, 27, 1, 12, 4, 3, 1, 2 },
            { 58, 2, 2, 12, 6, 1, 2, 21, 1, 2, 4, 1, 18, 3, 1, 28, 1, 14, 4, 1, 6, 2, 18, 2, 2, 110, 12, 6, 5 },
            { 2, 1, 4, 4, 5, 8, 2, 1, 144, 2, 1, 6, 1, 27, 2, 7, 4, 5, 2, 2, 3, 12, 1, 32, 7, 4, 4, 2, 1 },
            { 6, 3, 28, 13, 12, 6, 4, 6, 1, 11, 60, 10, 4, 2, 16, 2, 1, 29, 290, 9, 1, 2, 6, 112, 2, 3, 72, 20, 3 },
            { 1, 10, 203, 1, 36, 12, 1, 4, 2, 1, 7, 4, 1, 12, 32, 4, 58, 4, 1, 24, 4, 2, 1, 32, 12, 2, 4, 2, 1 },
            { 66, 29, 1, 3, 65, 1, 14, 1, 88, 2, 18, 3, 2, 2, 5, 1, 7, 1, 40, 1, 10, 18, 6, 1, 3, 1, 4, 10, 11 },
            { 42, 3, 9, 2, 1, 4, 1, 75, 4, 3, 1, 12, 6, 4, 1, 78, 1, 3, 10, 6, 5, 1, 2, 2, 4, 14, 20, 2, 1 },
            { 5, 2, 1, 5, 2, 24, 12, 2, 2, 10, 4, 1, 24, 1, 18, 2, 12, 1, 22, 2, 1, 3, 176, 6, 1, 6, 1, 2, 4 },
            { 8, 2, 6, 1, 95, 16, 8, 1, 4, 1, 5, 2, 6, 36, 165, 1, 4, 9, 2, 1, 9, 3, 2, 1, 29, 2, 10, 6, 2 },
            { 84, 4, 16, 10, 9, 2, 1, 6, 2, 2, 18, 3, 2, 18, 5, 4, 1, 2, 3, 51, 17, 24, 26, 7, 1, 2, 3, 84, 1 },
            { 1, 21, 3, 4, 1, 12, 4, 1, 16, 8, 65, 24, 3, 1, 2, 36, 4, 2, 6, 8, 203, 4, 1, 2, 6, 12, 4, 1, 16 },
            { 20, 1, 18, 2, 2, 4, 1, 15, 25, 1, 190, 252, 26, 5, 1, 2, 14, 3, 12, 1, 16, 1, 14, 6, 2, 1, 5, 2, 1 }
    };
    castleArea ( alt, 29, result );
    assert ( identicalMap ( result, area, 29 ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
